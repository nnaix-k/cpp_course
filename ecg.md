ECG 题三文件结构

1. ecg.h
负责：
- 定义 ECG 这个类型
- 声明所有函数

内容：

#pragma once
#include <string>
#include <vector>
#include <array>

struct ECG {
    double sampling_interval;
    std::vector<double> V;
};

ECG load_ecg(const std::string& filename);

std::vector<double> detect_r_peaks(const ECG& ecg, double V_threshold, double t_refract);

std::vector<double> compute_RR_intervals(const std::vector<double>& r_peaks);

std::array<double, 3> compute_min_mean_max(const std::vector<double>& rr_intervals);

double compute_RMSSD(const std::vector<double>& rr_intervals);

std::string stress_level(double rmssd);

void write_report(const std::string& output_file,
                  const std::string& input_file,
                  const std::array<double, 3>& rr_stats,
                  double rmssd,
                  const std::string& level);


2. ecg.cpp
负责：
- 真正实现这些函数

内容：

#include "ecg.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <stdexcept>

ECG load_ecg(const std::string& filename)
{
    std::ifstream infile(filename);

    if (!infile)
    {
        throw std::runtime_error("failed to open file");
    }

    std::string header;
    infile >> header;

    if (header != "ECG")
    {
        throw std::runtime_error("invalid file format");
    }

    ECG ecg;
    infile >> ecg.sampling_interval;

    double value;
    while (infile >> value)
    {
        ecg.V.push_back(value);
    }

    return ecg;
}

std::vector<double> detect_r_peaks(const ECG& ecg, double V_threshold, double t_refract)
{
    std::vector<double> peaks;
    double last_peak_time = -1e9;

    for (int i = 1; i < ecg.V.size() - 1; i++)
    {
        double t = i * ecg.sampling_interval;

        bool above_threshold = ecg.V[i] > V_threshold;
        bool local_max = ecg.V[i] > ecg.V[i - 1] && ecg.V[i] > ecg.V[i + 1];
        bool far_enough = (t - last_peak_time) >= t_refract;

        if (above_threshold && local_max && far_enough)
        {
            peaks.push_back(t);
            last_peak_time = t;
        }
    }

    return peaks;
}

std::vector<double> compute_RR_intervals(const std::vector<double>& r_peaks)
{
    std::vector<double> rr_intervals;

    for (int i = 1; i < r_peaks.size(); i++)
    {
        rr_intervals.push_back(r_peaks[i] - r_peaks[i - 1]);
    }

    return rr_intervals;
}

std::array<double, 3> compute_min_mean_max(const std::vector<double>& rr_intervals)
{
    double min_value = rr_intervals[0];
    double max_value = rr_intervals[0];
    double sum = 0.0;

    for (const auto& x : rr_intervals)
    {
        if (x < min_value)
        {
            min_value = x;
        }

        if (x > max_value)
        {
            max_value = x;
        }

        sum += x;
    }

    double mean = sum / rr_intervals.size();

    return {min_value, mean, max_value};
}

double compute_RMSSD(const std::vector<double>& rr_intervals)
{
    double sum = 0.0;

    for (int i = 1; i < rr_intervals.size(); i++)
    {
        double diff = rr_intervals[i] - rr_intervals[i - 1];
        sum += diff * diff;
    }

    return std::sqrt(sum / (rr_intervals.size() - 1));
}

std::string stress_level(double rmssd)
{
    if (rmssd > 50)
    {
        return "low";
    }
    else if (rmssd >= 20)
    {
        return "moderate";
    }
    else
    {
        return "high";
    }
}

void write_report(const std::string& output_file,
                  const std::string& input_file,
                  const std::array<double, 3>& rr_stats,
                  double rmssd,
                  const std::string& level)
{
    std::ofstream outfile(output_file);

    if (!outfile)
    {
        throw std::runtime_error("failed to open output file");
    }

    outfile << "Input file: " << input_file << "\n";
    outfile << "Minimum RR interval: " << rr_stats[0] << "\n";
    outfile << "Mean RR interval: " << rr_stats[1] << "\n";
    outfile << "Maximum RR interval: " << rr_stats[2] << "\n";
    outfile << "RMSSD: " << rmssd << "\n";
    outfile << "Stress level: " << level << "\n";
}


3. main.cpp
负责：
- 检查参数
- 设置默认值
- 调用函数
- 串起整个流程

内容：

#include <iostream>
#include <string>
#include "ecg.h"

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 3)
        {
            std::cerr << "ERROR: expected input and output filenames\n";
            return 1;
        }

        std::string input_file = argv[1];
        std::string output_file = argv[2];

        double V_threshold = 0.5;
        double t_refract = 0.3;

        if (argc > 3)
        {
            V_threshold = std::stod(argv[3]);
        }

        if (argc > 4)
        {
            t_refract = std::stod(argv[4]);
        }

        ECG ecg = load_ecg(input_file);

        std::vector<double> r_peaks = detect_r_peaks(ecg, V_threshold, t_refract);

        std::vector<double> rr_intervals = compute_RR_intervals(r_peaks);

        std::array<double, 3> rr_stats = compute_min_mean_max(rr_intervals);

        double rmssd = compute_RMSSD(rr_intervals);

        std::string level = stress_level(rmssd);

        write_report(output_file, input_file, rr_stats, rmssd, level);
    }
    catch (std::exception& err)
    {
        std::cerr << "ERROR: " << err.what() << "\n";
        return 1;
    }

    return 0;
}


怎么编译：

g++ main.cpp ecg.cpp -o ecg_program

怎么运行：

./ecg_program input.txt report.txt
./ecg_program input.txt report.txt 0.6 0.25


最短总结：

ecg.h
= 类型 + 声明

ecg.cpp
= 真正实现功能

main.cpp
= 串流程

顺序是：
main 调用函数
函数声明在 .h
函数定义在 .cpp
编译时 main.cpp 和 ecg.cpp 一起编译
