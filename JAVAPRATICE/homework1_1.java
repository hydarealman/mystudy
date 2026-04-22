// 状态/类型定义: 
public class homework1_1 {
    // 订单状态
    public enum OrderStatus {
        PENDING,    // 待支付
        PAID,       // 已支付
        SHIPPED,    // 已发货
        DELIVERED,  // 已送达
        CANCELLED;  // 已取消
    }

    public static class Order {
        private OrderStatus status;

        public Order() {
            this.status = OrderStatus.PENDING;
        }

        /*
            如果当前状态是PENDING,则改为PAID，打印"支付成功",否则
            打印"当前状态无法支付"
        */
        public void pay() {
            if (status == OrderStatus.PENDING) {
                status = OrderStatus.PAID;
                System.out.println("支付成功,状态变为: " + status);
            } else {
                System.out.println("当前状态无法支付");
            }
        }

        // 如果当前状态是PAID，则打印"已发货"
        public void ship() {
            if (status == OrderStatus.PAID) {
                System.out.println("已发货");
            } else {   
               System.out.println("只有已支付的订单才能发货"); 
            }
        }
    }

    public static void main(String[] args) {
        // 创建订单,初始状态设为PENDING(待支付)
        Order order = new Order();
        order.pay();    // 支付成功,状态变为: PAID
        order.ship();   // 已发货
    }
}
