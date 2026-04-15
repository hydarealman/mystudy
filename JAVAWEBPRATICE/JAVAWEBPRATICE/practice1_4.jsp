pageEncoding="UTF-8"
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>JSP脚本元素实验</title>
    <style>
        table, td { border: 1px solid black; border-collapse: collapse; }
        td { width: 40px; text-align: center; padding: 4px; }
    </style>
</head>
<body>

<h2>1. 输出26个小写英文字母表（使用Java程序片）</h2>
<%
    // Java程序片：这里的代码会原样放入 service 方法中
    for (char c = 'a'; c <= 'z'; c++) {
        out.print(c + " ");
    }
%>

<h2>2. 简单计数器（利用成员变量）</h2>
<%!
    // 声明成员变量（在类中，所有用户共享）
    private int visitCount = 0;
%>
<%
    // 每次访问页面，计数+1
    visitCount++;
%>
<p>您是第 <%= visitCount %> 位访问者。</p>
<p><small>提示：刷新页面或新开浏览器窗口，计数会增加。</small></p>

<h2>3. 输出15行×10列的表格（使用JSP脚本）</h2>
<table>
    <%
        int rows = 15;
        int cols = 10;
        for (int i = 1; i <= rows; i++) {
            out.println("<tr>");
            for (int j = 1; j <= cols; j++) {
                // 表格单元格内容可以自由定义，这里显示“行-列”
                out.println("<td>" + i + "-" + j + "</td>");
            }
            out.println("</tr>");
        }
    %>
</table>

</body>
</html>