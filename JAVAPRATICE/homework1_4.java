// 找质数（素数）
public class homework1_4 {
    
    /**
     * 判断一个整数是否为质数
     * @param n 要判断的数
     * @return true 表示是质数，false 表示不是
     */
    public static boolean isPrime(int n) {
        // 小于2的数都不是质数
        if (n < 2) {
            return false;
        }
        // 2 是质数
        if (n == 2) {
            return true;
        }
        // 偶数（除了2）都不是质数
        if (n % 2 == 0) {
            return false;
        }
        // 只需检查到平方根即可，从3开始，步长为2（只检查奇数）
        int limit = (int) Math.sqrt(n);
        for (int i = 3; i <= limit; i += 2) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }
    
    /**
     * 找出从 1 到 max 之间的所有质数，并打印
     * @param max 范围的最大值
     */
    public static void findPrimesUpTo(int max) {
        System.out.println("1 到 " + max + " 之间的质数有：");
        int count = 0;
        for (int i = 2; i <= max; i++) {
            if (isPrime(i)) {
                System.out.print(i + " ");
                count++;
                // 每输出10个换行，方便查看
                if (count % 10 == 0) {
                    System.out.println();
                }
            }
        }
        System.out.println("\n共找到 " + count + " 个质数。");
    }
    
    public static void main(String[] args) {
        // 示例1：判断单个数
        int testNum = 17;
        System.out.println(testNum + (isPrime(testNum) ? " 是质数" : " 不是质数"));
        
        // 示例2：找出100以内的所有质数
        findPrimesUpTo(100);
        
        // 示例3：演示边界情况
        System.out.println("\n边界测试：");
        System.out.println("0 是质数？ " + isPrime(0));
        System.out.println("1 是质数？ " + isPrime(1));
        System.out.println("2 是质数？ " + isPrime(2));
        System.out.println("9 是质数？ " + isPrime(9));
        System.out.println("97 是质数？ " + isPrime(97));
    }
}