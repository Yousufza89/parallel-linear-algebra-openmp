# parallel-linear-algebra-openmp
Parallel implementation of Cramer's Rule and Matrix Inversion using OpenMP to optimize performance for large-scale matrix computations.
# Parallel Linear Algebra with OpenMP

## 📌 Description
Implementation of matrix inversion and solution of linear systems using Cramer's Rule in both serial and parallelized form using OpenMP in C++.

## 📈 Project Focus
- Matrix Inversion for large matrices (up to size 5000)
- Cramer’s Rule for small matrices (up to size 11)
- Performance comparison with increasing threads

## 🛠 Tech Stack
- C++ with OpenMP
- Matrix and vector manipulation
- Performance logging

## ⚡ Results Summary
- Achieved significant speedup with 4-8 threads
- Scalability limitation for Cramer's Rule
- System bottleneck observed beyond 8 cores

## 🧪 Benchmark Highlights
- Matrix size 5000 reduced runtime from 1.5 hrs to 18 min
- Thread count scalability: 1 to 200

## 📂 Repo Structure

/src

matrix_inversion.cpp

cramer_rule.cpp /results

logs.txt

graphs/


