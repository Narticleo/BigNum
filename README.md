# BigNum

使用 C++ 實作大數高精度的運算，包含了複雜的非整數指數運算。透過自然底數的轉換，可用泰勒級數來逼近，並透過建表的方式無限逼近，以計算自然對數。成功的將複雜計算化為簡單加減法，大大提升計算效率。

為計算非整數的指數運算，需要將底數替換為自然數 $e$，即：
$$x^y = e^{y \ln x}$$

以 $e$ 為底數的指數即可透過泰勒級數求解，因此只需要能精準計算 $\ln x$ 值。透過對數的特性：
$$\ln x = \ln \frac{x}{y} + \ln y$$

可以使用簡化為：
$$\ln x = \ln \frac{x}{y_i \cdot y_j \cdot y_k} + \ln y_i + \ln y_j + \ln y_k$$

盡可能的使 $\frac{x}{y_i y_j y_k}$ 趨近於 $1$，透過事先建立好的高精度表格計算出 $\ln y_i + \ln y_j + \ln y_k$ 即可將複雜的計算精準且快速的收斂。

## $\ln$ 表格
<img width="514" height="669" alt="image" src="https://github.com/user-attachments/assets/3b33c7ea-e8ea-4d20-8e82-dd181dd9d6a6" />

