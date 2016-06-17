public class LCSTest {
    // 字符串编辑距离
    public static List<Integer> writeColor(String tpl, String text) {

        int[] ret = new int[text.length() + 1];
        int[][] dp = new int[tpl.length() + 1][text.length() + 1];
        int[][] data = new int[tpl.length() + 1][text.length() + 1];

        for (int i = 0; i <= tpl.length(); i++)
            dp[i][0] = i;
        for (int i = 0; i <= text.length(); i++)
            dp[0][i] = i;
        for (int i = 1; i <= tpl.length(); i++) {

            for (int j = 1; j <= text.length(); j++) {
                int k = Integer.MAX_VALUE;
                int choice = 0;
                if (tpl.charAt(i - 1) == text.charAt(j - 1)) {
                    k = dp[i - 1][j - 1];
                    choice = 1;//same
                }
                if (dp[i - 1][j] <= dp[i][j - 1] && dp[i - 1][j] <= dp[i - 1][j - 1]) {
                    if (dp[i - 1][j] < k) {
                        k = dp[i - 1][j];
                        choice = 2;//add
                    }
                } else if (dp[i][j - 1] <= dp[i - 1][j] && dp[i][j - 1] <= dp[i - 1][j - 1]) {
                    if (dp[i][j - 1] < k) {
                        k = dp[i][j - 1];
                        choice = 3;//sub
                    }
                } else if (dp[i - 1][j - 1] <= dp[i][j - 1] && dp[i - 1][j - 1] <= dp[i - 1][j]) {
                    if (dp[i - 1][j - 1] < k) {
                        k = dp[i - 1][j - 1];
                        choice = 4;//change
                    }
                }
                dp[i][j] = k + 1;
                data[i][j] = choice;
            }
        }
        int loc1 = tpl.length();
        int loc2 = text.length();
        while (dp[loc1][loc2] > 0 && loc1 > 0 && loc2 > 0) {
            if (data[loc1][loc2] == 1) {
                loc1--;
                loc2--;
            } else if (data[loc1][loc2] == 2) {
                ret[loc2--] = 1;//add
            } else if (data[loc1][loc2] == 3) {
                loc1--;
                ret[loc2] = 2;//sub
            } else {
                loc1--;
                loc2--;
                ret[loc2] = 3;
            }
        }
        List<Integer> ans = new ArrayList<>();
        for (int i = 1; i < ret.length; i++)
            ans.add(ret[i]);
        return ans;

    }

    public static class Node {
        int st;
        String subTpl;
        int length;
        int op;

        public Node(int st, int length, int op) {
            this.st = st;
            this.length = length;
            this.op = op;
        }

        public Node(int st, int length, int op, String subTpl) {
            this.length = length;
            this.op = op;
            this.st = st;
            this.subTpl = subTpl;
        }

        @Override public String toString() {
            return "Node{" +
                "length=" + length +
                ", st=" + st +
                ", op=" + op +
                '}';
        }
    }

    // 下标都是偏移+1
    // 1是相同 2 是多了 3 是少了
    public static List<Node> LCS(String tpl, String str, int strSt) {
        if (tpl.length() == 0 && str.length() == 0) {
            return new ArrayList<>();
        } else if (tpl.length() == 0) {
            return new ArrayList<>(Collections.singletonList(new Node(strSt, str.length(), 2)));
        } else if (str.length() == 0) {
            return new ArrayList<>(
                Collections.singletonList(new Node(strSt, tpl.length(), 3, tpl)));
        }

        int[][] dp = new int[tpl.length() + 1][str.length() + 1];
        int maxi, maxj, maxk;
        maxi = maxj = maxk = 0;
        for (int i = 1; i <= tpl.length(); i++) {
            for (int j = 1; j <= str.length(); j++) {
                if (tpl.charAt(i - 1) == str.charAt(j - 1)) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    if (dp[i][j] >= maxk) {
                        maxk = dp[i][j];
                        maxi = i;
                        maxj = j;
                    }
                }
            }
        }

        List<Node> list = new ArrayList<>();
        if (maxk == 0) {
            list.add(new Node(strSt, tpl.length(), 3, tpl));
            list.add(new Node(strSt, str.length(), 2));
        } else {
            list.addAll(LCS(tpl.substring(0, maxi - maxk), str.substring(0, maxj - maxk), strSt));

            list.add(new Node(maxj - maxk, maxk, 1));

            list.addAll(
                LCS(tpl.substring(maxi, tpl.length()), str.substring(maxj, str.length()), maxj));
        }
        return list;
    }

    public static void main(String args[]) {
        //        TemplateTestResult test =
        //            new TemplateTestResult("【#company#】您的验证码是#code#", "你好【啊啊啊】您的验证码是123", false);
        //        System.out.println(test.getFinalMessage());
        //        System.out.println(test.failStartPos + "," + test.failEndPos);
        //        System.out.println(writeColor("4123", "1234"));
        //        System.out.println(LCS("1234", "1235", 0));
        String tpl = "【#company#】您的验证码是#code#";
        String str = "你好【啊啊啊】您的验证码是123";
        List<Node> list = LCS(tpl, str, 0);
        for (Node node : list) {
            if (node.op == 1) {
                System.out.println("sam:" + str.substring(node.st, node.st + node.length));
            } else if (node.op == 2) {
                System.out.println("add:" + str.substring(node.st, node.st + node.length));
            } else if (node.op == 3) {
                System.out.println("sub:" + node.subTpl);
            }
        }
    }
}