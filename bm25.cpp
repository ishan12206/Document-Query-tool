#include <bits/stdc++.h>
using namespace std;

double k1 = 1.5;
double b = 0.75;

vector<string> tokenize(const string& text) {
    vector<string> tokens;
    string token;
    for (char ch : text) {
        if (isalnum(ch)) {
            token += tolower(ch);
        } else if (!token.empty()) {
            tokens.push_back(token);
            token.clear();
        }
    }
    if (!token.empty()) tokens.push_back(token);
    return tokens;
}

// Count term frequency in a document
unordered_map<string, int> term_frequency(const vector<string>& tokens) {
    unordered_map<string, int> tf;
    for (const string& word : tokens) {
        tf[word]++;
    }
    return tf;
}

// Compute document frequencies (DF) across corpus
unordered_map<string, int> document_frequency(const vector<vector<string>>& corpus) {
    unordered_map<string, int> df;
    for (const auto& doc : corpus) {
        unordered_set<string> unique_terms(doc.begin(), doc.end());
        for (const string& term : unique_terms) {
            df[term]++;
        }
    }
    return df;
}

double compute_idf(int N, int df) {
    return log((N - df + 0.5) / (df + 0.5) + 1);
}

double compute_bm25(const unordered_map<string, int>& tf_doc, const unordered_map<string, int>& df,
                    const vector<string>& doc, const vector<string>& query, double avgdl, int N) {
    double score = 0.0;
    for (const string& term : query) {
        if (tf_doc.count(term) == 0) continue;

        int tf = tf_doc.at(term);
        int df_term = df.count(term) ? df.at(term) : 0;
        double idf = compute_idf(N, df_term);

        double numerator = tf * (k1 + 1);
        double denominator = tf + k1 * (1 - b + b * doc.size() / avgdl);
        score += idf * (numerator / denominator);
    }
    return score;
}

int main() {
    vector<string> raw_docs = {
        "ChatGPT is a large language model developed by OpenAI.",
        "BM25 is a ranking function used in information retrieval.",
        "Porter stemming helps in normalizing words to their base form.",
        "Stemming algorithms like Porter help improve document retrieval accuracy.",
        "OpenAI's tools are widely used for natural language processing tasks."
    };

    string query_raw = "How does BM25 and stemming help in document search?";

    // Tokenize documents
    vector<vector<string>> corpus;
    vector<unordered_map<string, int>> tf_corpus;
    for (const string& doc : raw_docs) {
        vector<string> tokens = tokenize(doc);
        corpus.push_back(tokens);
        tf_corpus.push_back(term_frequency(tokens));
    }

    int N = corpus.size();
    double avgdl = 0.0;
    for (const auto& doc : corpus) avgdl += doc.size();
    avgdl /= N;

    // DF
    unordered_map<string, int> df = document_frequency(corpus);

    // Tokenize query
    vector<string> query = tokenize(query_raw);

    // Score each document
    vector<pair<double, int>> scores;
    for (int i = 0; i < N; ++i) {
        double score = compute_bm25(tf_corpus[i], df, corpus[i], query, avgdl, N);
        scores.emplace_back(score, i);
    }

    // Sort and print
    sort(scores.rbegin(), scores.rend());
    cout << "Top relevant documents:\n";
    for (const auto& [score, idx] : scores) {
        cout << "Score: " << fixed << setprecision(4) << score << " | Doc: " << raw_docs[idx] << "\n";
    }

    return 0;
}
