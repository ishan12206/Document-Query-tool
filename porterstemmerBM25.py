import math
import nltk
from collections import defaultdict
from nltk.stem import PorterStemmer
from nltk.tokenize import word_tokenize

# Download punkt tokenizer
nltk.download("punkt")

# Porter Stemmer
stemmer = PorterStemmer()

# Preprocessing function
def preprocess(text):
    tokens = word_tokenize(text.lower())
    return [stemmer.stem(token) for token in tokens if token.isalnum()]

# BM25 Class
class BM25:
    def __init__(self, corpus, k1=1.5, b=0.75):
        self.k1 = k1
        self.b = b
        self.corpus = [preprocess(doc) for doc in corpus]
        self.N = len(self.corpus)
        self.df = defaultdict(int)
        self.idf = {}
        self.avgdl = sum(len(doc) for doc in self.corpus) / self.N
        self.doc_len = [len(doc) for doc in self.corpus]
        self.tf = []

        for doc in self.corpus:
            freq = defaultdict(int)
            for word in doc:
                freq[word] += 1
            self.tf.append(freq)
            for word in freq:
                self.df[word] += 1

        for word, freq in self.df.items():
            self.idf[word] = math.log(1 + (self.N - freq + 0.5) / (freq + 0.5))

    def score(self, query, top_k=3):
        query_tokens = preprocess(query)
        scores = []
        for idx, doc in enumerate(self.corpus):
            score = 0
            for word in query_tokens:
                if word in self.tf[idx]:
                    tf = self.tf[idx][word]
                    numerator = tf * (self.k1 + 1)
                    denominator = tf + self.k1 * (1 - self.b + self.b * self.doc_len[idx] / self.avgdl)
                    score += self.idf.get(word, 0) * numerator / denominator
            scores.append((score, idx))
        scores.sort(reverse=True)
        return scores[:top_k]

# Sample Corpus
docs = [
    "ChatGPT is a large language model developed by OpenAI.",
    "BM25 is a ranking function used in information retrieval.",
    "Porter stemming helps in normalizing words to their base form.",
    "Stemming algorithms like Porter help improve document retrieval accuracy.",
    "OpenAI's tools are widely used for natural language processing tasks."
]

query = "How does BM25 and stemming help in document search?"

# Initialize and run
bm25 = BM25(docs)
top_results = bm25.score(query)

# Output results
for score, idx in top_results:
    print(f"Score: {score:.4f} | Document: {docs[idx]}")
