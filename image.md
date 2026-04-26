# Assessment 2：Image Metrics 题怎么按做题思路一步一步搭结构

这份笔记不是直接给最终答案，而是训练：

```text
看到题目
-> 先想最后 main 想长什么样
-> 再反推 .h
-> 最后补 .cpp
```

题目来源：

- [Assignment 2 README](https://github.com/jdtournier/cpp_assignment2_image_metrics/blob/main/README.md)

---

## 1. 第一步：先把题目翻译成中文步骤

看到题目，我先写：

```text
输入：
- input image file
- output report file

输出：
- report file
- segmented image file
- binary mask file

步骤：
1. 读图像文件
2. 计算 histogram
3. 找 histogram 的两个主峰
4. 找两个峰之间的 valley，得到 threshold
5. 用 threshold 生成 binary mask
6. 用 mask 和原图做 segmented image
7. 计算 metrics：
   - total cell area
   - mean intensity
   - variance
8. 写 report
9. 另存 mask 和 segmented image
```

这一步的目的：

```text
先把题目从一大段英文，变成一条处理流水线
```

---

## 2. 第二步：先想数据要怎么存

一张图像至少有：

- width
- height
- pixel values

所以第一反应应该是：

```text
这不是一个单独数字，要打包起来
```

所以想到：

```cpp
struct Image {
    int width;
    int height;
    std::vector<int> pixels;
};
```

---

## 3. 第三步：再想最后的指标要怎么存

题目最后要得到：

- threshold
- total cell area
- mean intensity
- variance

所以可以再定义一个：

```cpp
struct ImageMetrics {
    int threshold;
    int area;
    double mean_intensity;
    double variance;
};
```

这样后面写 report 会清楚很多。

---

## 4. 第四步：先想我希望 main 长什么样

我不先写细节，我先想 main 最后想长成：

```cpp
Image image = load_image(input_file);

std::vector<int> histogram = compute_histogram(image);
int threshold = compute_threshold(histogram);

Image mask = make_binary_mask(image, threshold);
Image segmented = segment_image(image, mask);

ImageMetrics metrics = compute_metrics(mask, segmented, threshold);

write_report(output_file, metrics);
save_image(make_mask_filename(input_file), mask);
save_image(make_segmented_filename(input_file), segmented);
```

这一步的意义：

```text
先决定我要“得到什么”
```

---

## 5. 第五步：根据 main 反推 .h

现在我不急着写函数内容。

我先把 `image_metrics.h` 里的内容列出来：

```cpp
#pragma once
#include <string>
#include <vector>

struct Image {
    int width;
    int height;
    std::vector<int> pixels;
};

struct ImageMetrics {
    int threshold;
    int area;
    double mean_intensity;
    double variance;
};

Image load_image(const std::string& filename);

std::vector<int> compute_histogram(const Image& image);

int compute_threshold(const std::vector<int>& histogram);

Image make_binary_mask(const Image& image, int threshold);

Image segment_image(const Image& image, const Image& mask);

ImageMetrics compute_metrics(const Image& mask,
                             const Image& segmented,
                             int threshold);

void write_report(const std::string& output_file,
                  const ImageMetrics& metrics);

void save_image(const std::string& filename, const Image& image);

std::string make_mask_filename(const std::string& input_file);

std::string make_segmented_filename(const std::string& input_file);
```

---

## 6. 第六步：先搭 main.cpp 骨架

先把 main 串起来：

```cpp
#include <iostream>
#include <string>
#include "image_metrics.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "ERROR: expected input image and output report filenames\n";
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];

    Image image = load_image(input_file);

    std::vector<int> histogram = compute_histogram(image);
    int threshold = compute_threshold(histogram);

    Image mask = make_binary_mask(image, threshold);
    Image segmented = segment_image(image, mask);

    ImageMetrics metrics = compute_metrics(mask, segmented, threshold);

    write_report(output_file, metrics);
    save_image(make_mask_filename(input_file), mask);
    save_image(make_segmented_filename(input_file), segmented);

    return 0;
}
```

这一步的目标：

```text
先让 main 看起来像一条完整流程
```

---

## 7. 第七步：现在才开始写 .cpp

这时候才开始真正实现函数。

我建议先写最简单的：

1. `make_mask_filename`
2. `make_segmented_filename`
3. `compute_histogram`
4. `make_binary_mask`
5. `segment_image`
6. `compute_metrics`
7. `write_report`
8. `load_image`
9. `save_image`
10. `compute_threshold`

原因：

```text
先拿最稳、最基础的分
最后再写最绕的 threshold 逻辑
```

---

## 8. 示例：先写文件名辅助函数

题目要求：

- `filename_mask.txt`
- `filename_seg.txt`

所以我先写最简单的函数：

```cpp
std::string make_mask_filename(const std::string& input_file)
{
    return input_file + "_mask.txt";
}

std::string make_segmented_filename(const std::string& input_file)
{
    return input_file + "_seg.txt";
}
```

如果后面要去掉 `.txt` 再拼，也可以改，但先把主流程跑通最重要。

---

## 9. 示例：compute_histogram

题目说：

```text
灰度值范围 0 到 255
h(i) = 强度 i 出现的次数
```

所以我会想到：

```cpp
std::vector<int> histogram(256, 0);
```

然后扫描所有像素：

```cpp
std::vector<int> compute_histogram(const Image& image)
{
    std::vector<int> histogram(256, 0);

    for (const auto& pixel : image.pixels)
    {
        histogram[pixel]++;
    }

    return histogram;
}
```

---

## 10. 示例：make_binary_mask

题目给了公式：

```text
M(i,j) = 0 if I(i,j) <= T
M(i,j) = 1 if I(i,j) > T
```

所以我会写：

```cpp
Image make_binary_mask(const Image& image, int threshold)
{
    Image mask;
    mask.width = image.width;
    mask.height = image.height;

    for (const auto& pixel : image.pixels)
    {
        if (pixel > threshold)
        {
            mask.pixels.push_back(1);
        }
        else
        {
            mask.pixels.push_back(0);
        }
    }

    return mask;
}
```

---

## 11. 示例：segment_image

题目说：

```text
S(i,j) = I(i,j) * M(i,j)
```

所以：

```cpp
Image segment_image(const Image& image, const Image& mask)
{
    Image segmented;
    segmented.width = image.width;
    segmented.height = image.height;

    for (int i = 0; i < image.pixels.size(); i++)
    {
        segmented.pixels.push_back(image.pixels[i] * mask.pixels[i]);
    }

    return segmented;
}
```

---

## 12. 示例：compute_metrics

题目要算：

- area = mask 里 1 的个数
- mean intensity
- variance

所以我会先分三步：

```cpp
ImageMetrics compute_metrics(const Image& mask,
                             const Image& segmented,
                             int threshold)
{
    ImageMetrics metrics;
    metrics.threshold = threshold;

    int area = 0;
    double sum = 0.0;

    for (int i = 0; i < mask.pixels.size(); i++)
    {
        if (mask.pixels[i] == 1)
        {
            area++;
            sum += segmented.pixels[i];
        }
    }

    metrics.area = area;
    metrics.mean_intensity = sum / area;

    double variance_sum = 0.0;

    for (int i = 0; i < mask.pixels.size(); i++)
    {
        if (mask.pixels[i] == 1)
        {
            double diff = segmented.pixels[i] - metrics.mean_intensity;
            variance_sum += diff * diff;
        }
    }

    metrics.variance = variance_sum / area;

    return metrics;
}
```

---

## 13. 示例：write_report

题目要求 report 至少包含：

- threshold
- total cell area
- mean intensity
- variance

所以写：

```cpp
void write_report(const std::string& output_file,
                  const ImageMetrics& metrics)
{
    std::ofstream outfile(output_file);

    if (!outfile)
    {
        throw std::runtime_error("failed to open output file");
    }

    outfile << "Optimal Threshold Calculated: " << metrics.threshold << "\n";
    outfile << "Total Cell Area: " << metrics.area << " pixels\n";
    outfile << "Mean Intensity: " << metrics.mean_intensity << "\n";
    outfile << "Variance: " << metrics.variance << "\n";
}
```

---

## 14. 示例：load_image

题目格式：

```text
100 150
100 101 109 102 ...
101 101 102 111 ...
...
```

所以我会写：

```cpp
Image load_image(const std::string& filename)
{
    std::ifstream infile(filename);

    if (!infile)
    {
        throw std::runtime_error("failed to open input image");
    }

    Image image;
    infile >> image.width >> image.height;

    int pixel;
    while (infile >> pixel)
    {
        image.pixels.push_back(pixel);
    }

    return image;
}
```

---

## 15. 示例：save_image

题目要求 mask 和 segmented image 都按和输入一样的格式保存。

所以：

```cpp
void save_image(const std::string& filename, const Image& image)
{
    std::ofstream outfile(filename);

    if (!outfile)
    {
        throw std::runtime_error("failed to open image output file");
    }

    outfile << image.width << " " << image.height << "\n";

    for (int i = 0; i < image.pixels.size(); i++)
    {
        outfile << image.pixels[i];

        if ((i + 1) % image.width == 0)
        {
            outfile << "\n";
        }
        else
        {
            outfile << " ";
        }
    }
}
```

---

## 16. 最后再写 compute_threshold

这一步最绕，所以我会留到后面。

题目要求：

1. 找 histogram 里两个主峰
2. 峰的定义：比前后 10 个邻居都高
3. 找两个峰之间最低点作为 threshold

所以这一步我会拆成三层思考：

```text
先找所有局部峰
-> 再选最高的两个
-> 再在它们中间找最小值位置
```

这一步你先不需要马上会写完整代码，但你要知道：

```text
它本质还是 vector + for + if
```

---

## 17. 这道题你真正要学会的顺序

```text
题目
-> 先写中文步骤
-> 先想 main 想长什么样
-> 根据 main 反推 struct 和函数声明
-> 最后一个函数一个函数补
```

---

## 18. 三部分关系

### image_metrics.h

负责：

```text
struct Image
struct ImageMetrics
所有函数声明
```

### image_metrics.cpp

负责：

```text
把每个函数真正写出来
```

### main.cpp

负责：

```text
参数检查
调用函数
串流程
```

---

## 19. 最重要的一句话

```text
先决定 main 想要什么
然后让 .h 和 .cpp 去服务 main
```
