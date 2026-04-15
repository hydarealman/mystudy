#include <iostream>
#include <utility>
using namespace std;

enum Color//枚举值表示颜色
{
	RED,
	BLACK
};

//节点
template<class K, class V>
struct RBTreeNode
{
	pair<K, V> _kv;//数据域
	RBTreeNode<K, V>* _left;//指向左孩子的指针
	RBTreeNode<K, V>* _right;//指向右孩子的指针
	RBTreeNode<K, V>* _parent;//指向父亲的指针
	Color _col;//颜色

	RBTreeNode(const pair<K, V>& kv)//节点构造
		:_kv(kv)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _col(RED)
	{}
};

//红黑树类
template<class K, class V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	//强制生成无参构造
	RBTree() = default;

	//拷贝构造
	RBTree(const RBTree<K, V>& t)
	{
		_root = _Copy(t._root);
	}

	//析构函数
	~RBTree()
	{
		_Destroy(_root);
	}

	//插入
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)//树为空，直接插入
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}
		
		//先查找合适的插入位置
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (kv.first < cur->_kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (kv.first > cur->_kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(kv);

		if (kv.first < parent->_kv.first)
		{
			parent->_left = cur;
		}
		else
		{
			parent->_right = cur;
		}
		cur->_parent = parent;

		//parent为红，进行平衡调整
		while (parent && parent->_col == RED)
		{
			//确定grandfather
			Node* grandfather = parent->_parent;

			if (parent == grandfather->_left)
			{
				//确定uncle
				Node* uncle = grandfather->_right;
				if (uncle && uncle->_col == RED)//uncle为红，仅变色
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					//继续向上判断
					cur = grandfather;
					parent = cur->_parent;
				}
				else//uncle为黑或不存在，旋转+变色
				{
					if (cur == parent->_left)//右单旋
					{
						RotateR(grandfather);

						//变色
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else//左右双旋
					{
						RotateL(parent);
						RotateR(grandfather);

						//变色
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;//旋转完成，直接跳出循环
				}
			}
			else
			{
				//确定uncle
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_col == RED)//uncle为红，仅变色
				{
					parent->_col = uncle->_col = BLACK;
					grandfather->_col = RED;

					//继续向上判断
					cur = grandfather;
					parent = cur->_parent;
				}
				else//uncle为黑或不存在，旋转+变色
				{
					if (cur == parent->_right)//左单旋
					{
						RotateL(grandfather);

						//变色
						parent->_col = BLACK;
						grandfather->_col = RED;
					}
					else//右左双旋
					{
						RotateR(parent);
						RotateL(grandfather);

						//变色
						cur->_col = BLACK;
						grandfather->_col = RED;
					}
					break;//旋转完成，直接跳出循环
				}
			}
		}

		//最后将根节点设置为黑色
		_root->_col = BLACK;
		return true;
	}

	//查找
	Node* Find(const K& key)
	{
		Node* cur = _root;
		while (cur)
		{
			if (key < cur->_kv.first)
			{
				cur = cur->_left;//小了往左走
			}
			else if (key > cur->_kv.first)
			{
				cur = cur->_right;//大了往右走
			}
			else
			{
				return cur;//找到了，返回
			}
		}
		return nullptr;//没找到，返回空指针
	}

	//中序遍历
	void Inorder()
	{
		_Inorder(_root);
	}

	//判断是否为合法红黑树
	bool IsValidRBTree()
	{
		//空树，合法
		if (_root == nullptr) return true;

		//根节点为红，非法
		if (_root->_col == RED)
		{
			cout << "根节点为红" << endl;
			return false;
		}

		int refNum = 0;//记录黑色节点个数
		Node* cur = _root;
		while (cur)
		{
			if (cur->_col == BLACK) refNum++;
			cur = cur->_left;
		}

		//递归检查所有路径
		return _Check(_root, 0, refNum);
	}
private:
	//右单旋
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR) subLR->_parent = parent;

		Node* ppNode = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent) ppNode->_left = subL;
			else ppNode->_right = subL;
			subL->_parent = ppNode;
		}
	}

	//左单旋
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL) subRL->_parent = parent;

		Node* ppNode = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent) ppNode->_left = subR;
			else ppNode->_right = subR;
			subR->_parent = ppNode;
		}
	}

	//中序遍历
	void _Inorder(Node* root)
	{
		if (root == nullptr) return;
		_Inorder(root->_left);
		cout << root->_kv.first << ' ' << root->_kv.second << endl;
		_Inorder(root->_right);
	}

	//拷贝构造
	Node* _Copy(Node* root, Node* parent = nullptr)
	{
		if (root == nullptr) return nullptr;
		Node* NewRoot = new Node(root->_kv);
		NewRoot->_col = root->_col;//复制颜色
		NewRoot->_parent = parent;//设置父指针

		//递归拷贝左子树和右子树
		NewRoot->_left = _Copy(root->_left, NewRoot);
		NewRoot->_right = _Copy(root->_right, NewRoot);
		return NewRoot;
	}

	//销毁
	void _Destroy(Node* root)
	{
		if (root == nullptr) return;
		_Destroy(root->_left);
		_Destroy(root->_right);
		delete root;
	}

	//路径检查
	bool _Check(Node* root, int num, const int refNum)
	{
		if (root == nullptr)
		{
			//遍历到空，进行黑色节点比较
			if (num != refNum)
			{
				cout << "黑色节点数量不相等" << endl;
				return false;
			}
			return true;
		}

		//检查是否有连续红色节点
		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << "有连续红色节点" << endl;
			return false;
		}

		//记录当前路径的黑色节点数
		if (root->_col == BLACK) num++;

		//递归检查左子树和右子树
		return _Check(root->_left, num, refNum) && _Check(root->_right, num, refNum);
	}

	Node* _root = nullptr;//根节点指针
};

int main()
{
	RBTree<int, int> t;
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };

	for (auto& e : a)
	{
		t.Insert({ e,e });
	}

	t.Inorder();
	cout << t.IsValidRBTree() << endl;
	return 0;
}