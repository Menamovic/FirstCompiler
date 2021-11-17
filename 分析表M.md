### 非递归下降分析器

- 简化文法，仅包含while循环文法分析

  **注：忽略空格**
  $$
  \begin{aligned}
  &(0)program \rightarrow block\\
  &(1)block \rightarrow {stmts}\\
  &(2)stmts \rightarrow stmt\ stmts | \varepsilon\\
  &(3)stmt \rightarrow id=expr;\\
  &(4)stmt \rightarrow while (bool) stmt\\
  &(5)stmt \rightarrow block\\
  &(6)bool \rightarrow expr\ bool'\\
  &(7)bool' \rightarrow < expr\\
  &(8)bool' \rightarrow <= expr\\
  &(9)bool' \rightarrow > expr\\
  &(10)bool' \rightarrow >= expr\\
  &(11)bool' \rightarrow \varepsilon\\
  &(12)expr \rightarrow term\ expr''\\
  &(13)expr'' \rightarrow expr'\ expr'' | \varepsilon\\
  &(14)expr' \rightarrow + term\\
  &(15)expr' \rightarrow - term\\
  &(16)term \rightarrow factor\ term''\\
  &(17)term'' \rightarrow term'\ term'' | \varepsilon\\
  &(18)term' \rightarrow * factor\\
  &(19)term' \rightarrow / factor\\
  &(20)factor \rightarrow (expr)\\
  &(21)factor \rightarrow id\\
  &(22)factor \rightarrow num\\
  \end{aligned}
  $$

- 手工构造分析表

|         | 标识符 |  =   |  ;   | while |  (   |  )   |  <   |  <=  |  >   |  >=  |  +   |  -   |  *   |  /   | num  |
| :-----: | :----: | :--: | :--: | :---: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: | :--: |
| program |        |      |      |       |      |      |      |      |      |      |      |      |      |      |      |
|  block  |        |      |      |       |      |      |      |      |      |      |      |      |      |      |      |
|  stmts  |        |      |      |       |      |      |      |      |      |      |      |      |      |      |      |
|  stmt   |        |      |      |       |      |      |      |      |      |      |      |      |      |      |      |
|  bool   |        |      |      |       |      |      |      |      |      |      |      |      |      |      |      |
|  bool'  |        |      |      |       |      |      |      |      |      |      |      |      |      |      |      |
|  expr   |        |      |      |       |      |      |      |      |      |      |      |      |      |      |      |
|  expr'  |        |      |      |       |      |      |      |      |      |      |      |      |      |      |      |
| expr''  |        |      |      |       |      |      |      |      |      |      |      |      |      |      |      |
|  term   |        |      |      |       |      |      |      |      |      |      |      |      |      |      |      |
|  term'  |        |      |      |       |      |      |      |      |      |      |      |      |      |      |      |
| term''  |        |      |      |       |      |      |      |      |      |      |      |      |      |      |      |
| factor  |        |      |      |       |      |      |      |      |      |      |      |      |      |      |      |

- 求First、Follow集

$$
\begin{aligned}
&First(program)=\{\}\\
&First(block)=\{\}\\
&First(stmts)=\{\}\\
&First(stmt)=\{\}\\
&First(bool)=\{\}\\
&First(bool')=\{\}\\
&First(expr)=\{\}\\
&First(expr')=\{\}\\
&First(expr'')=\{\}\\
&First(term)=\{\}\\
&First(term')=\{\}\\
&First(term'')=\{\}\\
&First(factor)=\{\}\\
\\
&Follow(program)=\{\}\\
&Follow(block)=\{\}\\
&Follow(stmts)=\{\}\\
&Follow(stmt)=\{\}\\
&Follow(bool)=\{\}\\
&Follow(bool')=\{\}\\
&Follow(expr)=\{\}\\
&Follow(expr')=\{\}\\
&Follow(expr'')=\{\}\\
&Follow(term)=\{\}\\
&Follow(term')=\{\}\\
&Follow(term'')=\{\}\\
&Follow(factor)=\{\}\\
\end{aligned}
$$

