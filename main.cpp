#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <utility>
using namespace std;

void convert_to_MD(string target_fiel, string output_file_name);

int main(int argc, char* argv[]){
    convert_to_MD(argv[1], argv[2]);

    return 0;
}

void convert_to_MD(string target_file, string output_file_name){
    fstream input_file;
    fstream output_file;
    string line;
    bool check_first_line = true;
 
    vector <pair <string, std::string > > convertion_pairs = {
        {"(.*)\\[\\*\\s(.*)\\](.*)", "$1**$2**$3  "},
        {"(.*)\\[\\*\\*(\\s.*)\\](.*)", "$1###$2$3  "},
        {"(.*)\\[\\*\\*\\*(\\s.*)\\](.*)", "$1##$2$3  "},
        {"(.*)\\[\\*\\*\\*\\*(\\s.*)\\](.*)", "$1#$2$3  "},
        {"(.*)", "$1  "},
    };

    input_file.open(target_file);
    output_file.open(output_file_name, ios::out | ios::app); //結果出力ファイル (ファイルが存在しなければ作成する)

    if(!input_file.is_open() || !output_file.is_open()){
        cerr << "ファイルが開けませんでした" << endl;
    } else{
        while (getline(input_file, line)){
            //ページタイトルの変換
            if(check_first_line){
                check_first_line = false;
                line = line + '\n';
                regex first_line_pattern("(.*)\n");
                string first_line_replacement = "# $1";
                output_file << regex_replace(line, first_line_pattern, first_line_replacement) << endl;
                continue;
            }

            //文字列先頭の空白の数をチェック
            int space_counter = 0;
            line = regex_replace(line, regex("\xE3\x80\x80"), "\x20");
            for(int i=0; i<line.size(); i++){
                wchar_t checker = line[i];
                if(checker == 0x20 || checker == '\t'){ 
                    space_counter++;
                }
            }

            //空白の数に応じて文字列を変換
            if(space_counter > 0){
                regex space_remove_pattern("^\\s*(.*?)(\\s*\\*)?$");
                string space_replacement = "* $1";
                line = regex_replace(line, space_remove_pattern, space_replacement);
                for(int j=0; j<space_counter; j++){
                    line = "\x20\x20" + line;
                }
            }

            //文字装飾のチェック
            for (int i=0; i<convertion_pairs.size(); i++) {
                regex match_pattern(convertion_pairs[i].first);
                if(regex_match(line, match_pattern)){
                    string replacement = convertion_pairs[i].second;
                    output_file << regex_replace(line, match_pattern, replacement) << endl;
                    break;
                }
            } 
        }

        input_file.close();
        output_file.close();
    }
}