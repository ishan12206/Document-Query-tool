# 📚 BM25 Document Ranking Engine (C++)

A lightweight C++ implementation of the [BM25 ranking algorithm](https://en.wikipedia.org/wiki/Okapi_BM25), used for scoring and ranking documents based on query relevance. This project includes:

- Manual tokenization
- Term Frequency (TF)
- Document Frequency (DF)
- Inverse Document Frequency (IDF)
- BM25 scoring logic

---

## 🚀 Features

- ✅ Manual BM25 formula implementation (no external libraries)
- ✅ Easy to understand and modify
- ✅ Query against small or large text corpora
- ✅ Outputs top-matching documents with BM25 scores

---

## 📄 BM25 Formula

\[
\text{BM25}(D, Q) = \sum_{t \in Q} \text{IDF}(t) \cdot \frac{f(t, D) \cdot (k_1 + 1)}{f(t, D) + k_1 \cdot \left(1 - b + b \cdot \frac{|D|}{\text{avgdl}}\right)}
\]

Where:
- \( f(t, D) \): frequency of term `t` in document `D`
- \( |D| \): number of terms in document `D`
- \( \text{avgdl} \): average document length across corpus
- \( \text{IDF}(t) = \log\left(\frac{N - \text{df}(t) + 0.5}{\text{df}(t) + 0.5} + 1\right) \)

---
