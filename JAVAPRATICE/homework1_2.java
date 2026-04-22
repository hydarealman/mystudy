// 策略模式
// 根据不同类型执行不同的算法

public class homework1_2 {
    // 示例：计算器，根据运算符执行不同运算
public enum Calculator {
    ADD("+") { // 相当于 new Calculator("+") { ... }
        @Override /// 这是一个注解: 告诉编译器 下面这个方法是重写父类的抽象
        public double apply(double a, double b) {
            return a + b;
        }
    },
    SUBTRACT("-") {
        @Override
        public double apply(double a, double b) {
            return a - b;
        }
    },
    MULTIPLY("*") {
        @Override
        public double apply(double a, double b) {
            return a * b;
        }
    },
    DIVIDE("/") {
        @Override
        public double apply(double a, double b) {
            if (b == 0) {
                throw new ArithmeticException("除数不能为0");
            }
            return a / b;
        }
    };
    
    private String symbol;
    
    Calculator(String symbol) {
        this.symbol = symbol;
    }
    
    public String getSymbol() {
        return symbol;
    }
    
    // 抽象方法，每个枚举常量必须实现: 相当于cpp里面的纯虚函数吧
    public abstract double apply(double a, double b);
    
    // 使用示例
    /*
        Calculator.values()
        values是编译器自动为每个枚举类生成的一个静态方法
        它返回一个数组,里面包含了该枚举类型中声明的所有枚举常量顺序与声明顺序一致
    */
    public static void main(String[] args) {
        double x = 10, y = 5;
        for (Calculator op : Calculator.values()) {
            System.out.printf("%.0f %s %.0f = %.0f%n", x, op.getSymbol(), y, op.apply(x, y));
        }
    }
}
}
