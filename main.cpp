#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>
#include <bitset>

using namespace std;

// لایه 1: تولید هسته امن با استفاده از آنتروپی ترکیبی
string generate_core(int min_len=18, int max_len=26) {
    static vector<string> chaos_patterns = {
        "t$B", "kL@", "9!q", "Px7", "Z3#", "m^a"
    };
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> len_dist(min_len, max_len);
    uniform_int_distribution<int> pat_dist(0, chaos_patterns.size()-1);
    
    int length = len_dist(gen);
    string core;
    
    for(int i=0; i<length; i++) {
        bitset<8> byte(rd());
        core += static_cast<char>((byte.to_ulong() % 94) + 33);
    }
    
    // تزریق الگوهای آشوبی
    for(int i=0; i<3; i++) {
        int pos = rd() % (core.length() - 3);
        core.replace(pos, 3, chaos_patterns[pat_dist(gen)]);
    }
    
    return core;
}

// لایه 2: رمزگذاری چرخشی بیتی پیشرفته
void bitwise_rotation(string& str) {
    const vector<int> rot_table = {3,5,2,7,1,4,6,2};
    for(size_t i=0; i<str.size(); i++) {
        bitset<8> b(str[i]);
        int rot = rot_table[i % rot_table.size()];
        b = (b << rot) | (b >> (8 - rot));
        str[i] = static_cast<char>(b.to_ulong());
    }
}

// لایه 3: سیستم جایگزینی پویا
void dynamic_substitution(string& str) {
    const string cipher_map = 
        "QqWwEeRrTtYyUuIiOoPpAaSsDdFfGgHhJjKkLlZzXxCcVvBbNnMm!@#$%^&*";
    
    random_device rd;
    mt19937 gen(rd());
    
    for(auto& c : str) {
        int offset = (c % 32) + rd() % 16;
        c = cipher_map[(offset + rd() % 8) % cipher_map.size()];
    }
}

// لایه 4: رمزگذاری چند کلیدی
void multi_key_xor(string& str) {
    vector<int> dynamic_keys = {
        static_cast<int>(str.length() % 255),
        static_cast<int>(str[0]),
        static_cast<int>(str.back())
    };
    
    for(size_t i=0; i<str.size(); i++) {
        str[i] ^= dynamic_keys[i % dynamic_keys.size()] + i;
        str[i] = (str[i] % 94) + 33; // حفظ محدوده قابل چاپ
    }
}

// لایه 5: تابع درهم‌سازی ترکیبی
string hybrid_hash(const string& input) {
    const int prime1 = 0x01000193;
    const int prime2 = 0x811C9DC5;
    uint32_t hash = prime2;

    for(char c : input) {
        hash ^= (c & 0xFF);
        hash *= prime1;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    
    string output;
    for(int i=0; i<8; i++) {
        output += (hash % 94) + 33;
        hash >>= 4;
    }
    
    return output;
}

// لایه 6: سیستم تغییر شکل تطبیقی
void adaptive_morph(string& str) {
    const vector<string> morph_patterns = {
        "s3K", "d$8", "vF5", "jL!", "q2@", "z9#"
    };
    
    random_device rd;
    mt19937 gen(rd());
    
    for(int i=0; i<2; i++) {
        int pos = rd() % (str.length() - 3);
        str.insert(pos, morph_patterns[rd() % morph_patterns.size()]);
    }
    
    // حفظ طول ثابت با حذف کاراکترهای انتهایی
    if(str.length() > 24) str = str.substr(0, 24);
}

// لایه 7: رمزگذاری نهایی کوانتومی
void quantum_finalize(string& str) {
    random_device rd;
    mt19937 gen(rd());
    
    for(auto& c : str) {
        bitset<8> b(c);
        if(rd() % 2) b.flip(rd() % 8);
        c = static_cast<char>((b.to_ulong() % 94) + 33);
    }
    
    shuffle(str.begin(), str.end(), gen);
}

string generate_quantum_password() {
    string password = generate_core();
    
    bitwise_rotation(password);
    dynamic_substitution(password);
    multi_key_xor(password);
    adaptive_morph(password);
    
    string hash_part = hybrid_hash(password);
    password += hash_part.substr(0, 4);
    
    quantum_finalize(password);
    
    return password.substr(0, 24); // طول ثابت 24 کاراکتر
}

int main() {
    cout << "رمز کوانتومی امن: " << generate_quantum_password() << endl;
    return 0;
}
