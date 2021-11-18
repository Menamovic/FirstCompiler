### 非递归下降分析器

- 消除间接左递归方法

例：
$$
\begin{aligned}
&S \rightarrow Qc|c\\
&Q \rightarrow Rb|b\\
&R \rightarrow Sa|a\\
\\
&过程：\\
&(1)代入化简，将间接左递归变成直接左递归\\ 
&将R的产生式代入Q的产生式，得到\\
&Q \rightarrow Sab|ab|b\\
&将Q的产生式代入S的产生式，得到\\
&S \rightarrow Sabc|abc|bc|c\\
&(2)消除直接左递归，得到的结果与Q和R无关，可删去Q和R的产生式\\
&S \rightarrow abcS'|bcS'|cS'\\
&S' \rightarrow abcS'|\varepsilon\\
\end{aligned}
$$

- 简化文法，仅包含while循环的文法分析

**注：以空格分隔各符号（终结符与非终结符）**
$$
\begin{aligned}
&(0)program \rightarrow block\\
&(1)block \rightarrow \{\ stmts\ \}\\
&(2)stmts \rightarrow stmt\ stmts\\
&(3)stmts \rightarrow \varepsilon\\
&(4)stmt \rightarrow id\ =\ expr\ ;\\
&(5)stmt \rightarrow while\ (\ bool\ )\ stmt\\
&(6)stmt \rightarrow block\\
&(7)bool \rightarrow expr\ bool'\\
&(8)bool' \rightarrow <\ expr\\
&(9)bool' \rightarrow <=\ expr\\
&(10)bool' \rightarrow >\ expr\\
&(11)bool' \rightarrow >=\ expr\\
&(12)bool' \rightarrow \varepsilon\\
&(13)expr \rightarrow term\ expr''\\
&(14)expr'' \rightarrow expr'\ expr''\\
&(15)expr'' \rightarrow \varepsilon\\
&(16)expr' \rightarrow +\ term\\
&(17)expr' \rightarrow -\ term\\
&(18)term \rightarrow factor\ term''\\
&(19)term'' \rightarrow term'\ term''\\
&(20)term'' \rightarrow \varepsilon\\
&(21)term' \rightarrow *\ factor\\
&(22)term' \rightarrow /\ factor\\
&(23)factor \rightarrow (\ expr\ )\\
&(24)factor \rightarrow id\\
&(25)factor \rightarrow num\\
\end{aligned}
$$

- 手工构造分析表

|             |                 {                 |                 }                 |                 id                  |  =   |  ;   |               while               |                  (                  |                  )                   |                  <                   |                  <=                  |                  >                   |                  >=                  |                  +                   |                  -                   |                  *                   |                  /                   |                 num                 |
| :---------: | :-------------------------------: | :-------------------------------: | :---------------------------------: | :--: | :--: | :-------------------------------: | :---------------------------------: | :----------------------------------: | :----------------------------------: | :----------------------------------: | :----------------------------------: | :----------------------------------: | :----------------------------------: | :----------------------------------: | :----------------------------------: | :----------------------------------: | :---------------------------------: |
| **program** |   $$program \rightarrow block$$   |                                   |                                     |      |      |                                   |                                     |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                     |
|  **block**  |  $$block \rightarrow \{stmts\}$$  |                                   |                                     |      |      |                                   |                                     |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                     |
|  **stmts**  | $$stmts \rightarrow stmt\ stmts$$ | $$stmts \rightarrow \varepsilon$$ |  $$stmts \rightarrow stmt\ stmts$$  |      |      | $$stmts \rightarrow stmt\ stmts$$ |                                     |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                     |
|  **stmt**   |    $$stmt \rightarrow block$$     |                                   |    $$stmt \rightarrow id=expr;$$    |      |      |       $$while (bool) stmt$$       |                                     |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                     |
|  **bool**   |                                   |                                   |  $$bool \rightarrow expr\ bool'$$   |      |      |                                   |  $$bool \rightarrow expr\ bool'$$   |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |  $$bool \rightarrow expr\ bool'$$   |
|  **bool'**  |                                   |                                   |                                     |      |      |                                   |                                     |  $$bool' \rightarrow \varepsilon$$   |     $$bool' \rightarrow < expr$$     |    $$bool' \rightarrow <= expr$$     |     $$bool' \rightarrow > expr$$     |    $$bool' \rightarrow >= expr$$     |                                      |                                      |                                      |                                      |                                     |
|  **expr**   |                                   |                                   |  $$expr \rightarrow term\ expr''$$  |      |      |                                   |  $$expr \rightarrow term\ expr''$$  |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |  $$expr \rightarrow term\ expr''$$  |
|  **expr'**  |                                   |                                   |                                     |      |      |                                   |                                     |                                      |                                      |                                      |                                      |                                      |     $$expr' \rightarrow + term$$     |     $$expr' \rightarrow - term$$     |                                      |                                      |                                     |
| **expr''**  |                                   |                                   |                                     |      |      |                                   |                                     | $$expr'' \rightarrow \varepsilon\\$$ | $$expr'' \rightarrow \varepsilon\\$$ | $$expr'' \rightarrow \varepsilon\\$$ | $$expr'' \rightarrow \varepsilon\\$$ | $$expr'' \rightarrow \varepsilon\\$$ | $$expr'' \rightarrow expr'\ expr''$$ | $$expr'' \rightarrow expr'\ expr''$$ |                                      |                                      |                                     |
|  **term**   |                                   |                                   | $$term \rightarrow factor\ term''$$ |      |      |                                   | $$term \rightarrow factor\ term''$$ |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      | $$term \rightarrow factor\ term''$$ |
|  **term'**  |                                   |                                   |                                     |      |      |                                   |                                     |                                      |                                      |                                      |                                      |                                      |                                      |                                      |    $$term' \rightarrow * factor$$    |    $$term' \rightarrow / factor$$    |                                     |
| **term''**  |                                   |                                   |                                     |      |      |                                   |                                     |  $$term'' \rightarrow \varepsilon$$  |  $$term'' \rightarrow \varepsilon$$  |  $$term'' \rightarrow \varepsilon$$  |  $$term'' \rightarrow \varepsilon$$  |  $$term'' \rightarrow \varepsilon$$  |                                      |                                      | $$term'' \rightarrow term'\ term''$$ | $$term'' \rightarrow term'\ term''$$ |                                     |
| **factor**  |                                   |                                   |      $$factor \rightarrow id$$      |      |      |                                   |    $$factor \rightarrow (expr)$$    |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |                                      |     $$factor \rightarrow num$$      |

- 求First集、Follow集

$$
\begin{aligned}
&First(program)=\{\ \{\ \}\\
&First(block)=\{\ \{\ \}\\
&First(stmts)=\{id,while,\{,\varepsilon\}\\
&First(stmt)=\{id,while,\{\ \}\\
&First(bool)=\{(,id,num\}\\
&First(bool')=\{<,<=,>,>=,\varepsilon\}\\
&First(expr)=\{(,id,num\}\\
&First(expr')=\{+,-\}\\
&First(expr'')=\{+,-,\varepsilon\}\\
&First(term)=\{(,id,num\}\\
&First(term')=\{*,/\}\\
&First(term'')=\{*,/,\varepsilon\}\\
&First(factor)=\{(,id,num\}\\
\\
&Follow(program)=\{\#\}\\
&Follow(block)=\{\#,id,while,(,\}\ \}\\
&Follow(stmts)=\{\ \}\ \}\\
&Follow(stmt)=\{id,while,(,\}\ \}\\
&Follow(bool)=\{)\}\\
&Follow(bool')=\{)\}\\
&Follow(expr)=\{),<,<=,>,>=\}\\
&Follow(expr')=\{+,-,),<,<=,>,>=\}\\
&Follow(expr'')=\{),<,<=,>,>=\}\\
&Follow(term)=\{+,-,),<,<=,>,>=\}\\
&Follow(term')=\{*,/,+,-,),<,<=,>,>=\}\\
&Follow(term'')=\{+,-,),<,<=,>,>=\}\\
&Follow(factor)=\{*,/,+,-,),<,<=,>,>=\}\\
\end{aligned}
$$

