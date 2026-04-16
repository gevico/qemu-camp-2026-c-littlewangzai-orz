# 位图操作笔记

## 一、位图是什么

用**一个 bit** 表示一个状态（0 或 1），把很多 bit 紧凑地存在字节数组里。

```
10 个位，只需要 2 个字节（16 bit），比用 10 个 int 省 20 倍内存
```

常见用途：记录某个数字"是否出现过"、布隆过滤器、操作系统空闲页面管理。

---

## 二、内存布局

```
bitmap[0]                    bitmap[1]
+----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
| 7  | 6  | 5  | 4  | 3  | 2  | 1  | 0  |  | 15 | 14 | 13 | 12 | 11 | 10 |  9 |  8 |
+----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
```

第 `bit_index` 位存在：
- **字节位置**：`bit_index / 8`
- **字节内偏移**：`bit_index % 8`

---

## 三、为什么不能直接 `bitmap + bit_index`

指针移动的单位是**字节**，不是位：

```c
bitmap + 5   // 移动 5 个字节 = 跳过 40 位  ❌
             // 想要的是第 5 位，在 bitmap[0] 里
```

必须先 `/8` 找字节，再 `%8` 找位。

---

## 四、核心操作

### 分配位图

```c
size_t bits = 10;
size_t bytes = (bits + 7) / 8;          // 向上取整：10 位需要 2 字节
unsigned char *bitmap = calloc(bytes, 1); // calloc 自动清零
```

### set_bit：将第 n 位置 1

```c
void set_bit(unsigned char *bitmap, size_t bit_index) {
    bitmap[bit_index / 8] |= (1 << (bit_index % 8));
}
```

原理：用掩码把目标位置 1，其余位不变：
```
bit_index = 5
掩码 = 1 << 5 = 0b00100000
bitmap[0] |= 0b00100000   → 第 5 位变成 1
```

### clear_bit：将第 n 位清 0

```c
void clear_bit(unsigned char *bitmap, size_t bit_index) {
    bitmap[bit_index / 8] &= ~(1 << (bit_index % 8));
}
```

原理：掩码取反后 `&`，目标位变 0，其余位不变：
```
掩码 = ~(1 << 5) = 0b11011111
bitmap[0] &= 0b11011111   → 第 5 位变成 0
```

### test_bit：读取第 n 位

```c
int test_bit(const unsigned char *bitmap, size_t bit_index) {
    return (bitmap[bit_index / 8] >> (bit_index % 8)) & 1;
}
```

原理：把目标位移到最低位，再和 1 相与，得到 0 或 1：
```
bit_index = 5
bitmap[0] >> 5            → 把第 5 位移到第 0 位
& 1                       → 取最低位，其余清零
```

---

## 五、位运算速查

| 操作 | 写法 | 作用 |
|------|------|------|
| 置 1 | `x \|= (1 << n)` | 第 n 位设为 1 |
| 清 0 | `x &= ~(1 << n)` | 第 n 位设为 0 |
| 取反 | `x ^= (1 << n)` | 第 n 位翻转 |
| 读取 | `(x >> n) & 1` | 读第 n 位的值 |

---

## 六、常见错误

### 错误一：对指针做位运算

```c
bitmap |= (1 << bit_index);   // ❌ bitmap 是指针，不是字节值
*bitmap |= (1 << bit_index);  // ❌ 只操作了第 0 个字节
bitmap[bit_index / 8] |= (1 << (bit_index % 8));  // ✅
```

### 错误二：字节数计算忘记向上取整

```c
size_t bytes = bits / 8;       // ❌ 10/8=1，只分配 1 字节，第 8-9 位越界
size_t bytes = (bits + 7) / 8; // ✅ (10+7)/8=2，正确分配 2 字节
```

### 错误三：移位用 int 类型溢出

```c
1 << 31    // ❌ int 溢出，未定义行为
1u << 31   // ✅ unsigned int
(unsigned char)1 << bit_index  // ✅ 明确类型
```
