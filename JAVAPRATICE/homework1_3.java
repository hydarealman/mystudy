// 同一返回码
public class homework1_3 {
    // 统一返回码枚举
    public enum ResultCode {
        SUCCESS(200, "操作成功"),
        BAD_REQUEST(400, "请求参数错误"),
        UNAUTHORIZED(401, "未登录或登录过期"),
        FORBIDDEN(403, "无权限访问"),
        NOT_FOUND(404, "资源不存在"),
        INTERNAL_ERROR(500, "服务器内部错误");


        private final int code;
        private final String message;
        
        ResultCode(int code, String message) {
            this.code = code;
            this.message = message;
        }
        
        public int getCode() {
            return code;
        }
        
        public String getMessage() {
            return message;
        }
        
        // 根据 code 获取枚举（反向查找）
        public static ResultCode fromCode(int code) {
            for (ResultCode rc : ResultCode.values()) {
                if (rc.code == code) {
                    return rc;
                }
            }
            return null;
        }
        
        @Override
        public String toString() {
            return String.format("{\"code\":%d,\"message\":\"%s\"}", code, message);
        }
    }

    public static class LoginService {
        public ResultCode login(String username, String password) {
            if (username == null || username.trim().isEmpty()) {
                return ResultCode.BAD_REQUEST;
            }
            if ("admin".equals(username) && "123456".equals(password)) {
                return ResultCode.SUCCESS;
            }
            return ResultCode.UNAUTHORIZED;
        }
    }
    
    public static void main(String[] args) {
        LoginService service = new LoginService();
        ResultCode result = service.login("admin", "wrong");
        System.out.println(result);  // 输出：{"code":401,"message":"未登录或登录过期"}
        System.out.println("状态码：" + result.getCode() + "，消息：" + result.getMessage());
    }
}


