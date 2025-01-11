# cpp-compile-time-brainfxxk

cpp-compile-time-brainfxxkはC++によるメタプログラミングを利用したコンパイル時brainfxxkインタプリタです．

## How To Run
### 実行するプログラムの選択

main.cpp内で`run_this_program`マクロを`#include brainfxxk_runtime.hpp`の前に呼び出します．

`main.cpp`
```c++
#include <iostream>

#include "brainfxxks.hpp" // brainfxxk programs

// need to call this macro before include brainfxxk_runtime.hpp
run_this_program(hello_world);

#include "brainfxxk_runtime.hpp"

int main() { std::cout << unwrap<brainfxxk<>::out>::value; }

```

`hello_world`は[brainfxxks.hppヘッダー](https://github.com/oonishi-daijiro/cpp-compile-time-brainfxxk/blob/master/brainfxxks.hpp)に記載されているサンプルプログラムです．
任意のBrainfuckプログラムを実行する場合，`run_this_program`マクロに`typearray<...>`を渡します．
Brainfuckのコードは以下の表を参考にして作成してください．

|                   |                          |
| :---------------: | :----------------------: |
| Brainfuckのコード | このプログラムでのコード |   
| +                 | inc                      |
| -                 | dec                      |
| >                 | iptr                     |
| <                 | dptr                     |
| .                 | out                      |
| ,                 | in                       |
| [                 | lb                       |
| ]                 | le                       |

例）
`.+[.+]` → `typearray<out,inc,lb,out,inc,le>`


### 入力
`brainfxxk`を`std::integer_sequence<memory_type,...>`で特殊化することで入力を渡します．<br><br>
例）
`brainfxxk<memory_type,1,2,3>::out`

### Build
```
git clone https://github.com/oonishi-daijiro/cpp-compile-time-brainfxxk && cd cpp-compile-time-brainfxxk
```
```
g++ main.cpp -std=c++20 -ftemplate-depth=1000000

または

CMakeでbuild
```

