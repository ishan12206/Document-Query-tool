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

## 📄 BM25 Scoring Formula

The BM25 score between a document \( D \) and a query \( Q \) is given by:

\[
\text{BM25}(D, Q) = \sum_{t \in Q} \text{IDF}(t) \cdot \frac{f(t, D) \cdot (k_1 + 1)}{f(t, D) + k_1 \cdot \left(1 - b + b \cdot \frac{|D|}{\text{avgdl}}\right)}
\]

### Parameters:

- \( f(t, D) \): Frequency of term \( t \) in document \( D \)
- \( |D| \): Number of terms in document \( D \)
- \( \text{avgdl} \): Average document length in the corpus
- \( k_1 \): Term frequency scaling parameter (typically between 1.2 and 2.0)
- \( b \): Length normalization parameter (usually 0.75)

### Inverse Document Frequency:

\[
\text{IDF}(t) = \log\left(\frac{N - \text{df}(t) + 0.5}{\text{df}(t) + 0.5} + 1\right)
\]

Where:
- \( N \): Total number of documents in the corpus
- \( \text{df}(t) \): Number of documents containing term \( t \)

> The BM25 score increases with term frequency but has diminishing returns, and it downweights common terms across the corpus.
