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
 

 /*
 ScrapBoxでは、*の数が増えるほど文字が大きくなるが、MDでは#が少ないほど文字が大きく、vscodeのveiwerでは6つがMax値
 htmlとCSSを使う方法もあり。vscodeのviewerでは対応あり
 ####が普通の文字と同じサイズなので、「####」 -> 「**太文字**」にする
 ### -> **
 ##  -> ***
 #   -> ****
※補足※
*５以上の大きさはHTML/CSSで対応可能だが、一旦実装は保留

 １行目は#にする(ページタイトルは最大文字)
 */
    vector <pair <string, std::string > > convertion_pairs = {
        {"(.*)\\[\\*\\s(.*)\\](.*)", "$1**$2**$3  "},
        {"(.*)\\[\\*\\*(\\s.*)\\](.*)", "$1###$2$3  "},
        {"(.*)\\[\\*\\*\\*(\\s.*)\\](.*)", "$1##$2$3  "},
        {"(.*)\\[\\*\\*\\*\\*(\\s.*)\\](.*)", "$1#$2$3  "},
        {"(.*)", "$1  "}
    };

    input_file.open(target_file);
    output_file.open(output_file_name, ios::out | ios::app); //ファイルが存在しなければ作成する

    if(!input_file.is_open() || !output_file.is_open()){
        cerr << "ファイルが開けませんでした" << endl;
    } else{
        while (getline(input_file, line)){

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