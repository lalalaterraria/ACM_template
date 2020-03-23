最经典的计数，给定$A$集合，$B$集合，求满足$a+b=c,a \in A,b \in B$的每一个$c$的数量

多个多项式作乘法，启发式合并来保证$nlgnlgn$的复杂度，即挑选当前多项式集合长度最小的两个合并

二维$FFT$，横向点值展开，再纵向点值展开，卷积，纵向点值还原，很向点值还原。

$DP[i][j]=DP[i-1][j]+DP[i][j-1]，已知 \forall i:DP[0][i]$，那么$DP[n]=DP[0] * [C_n^n,C_{n+1}^n.C_{n+2}^n...]$

$若b_i=\sum_{j=i-kx}a_j，即a_i每相隔k在b上提供一次贡献，则\sum b_ix^i=\sum a_ix^i\sum x^ik$

多项式定理，$(\sum x^{ik})^n=\sum(^{n+i-1}_i)x^{ik}$

