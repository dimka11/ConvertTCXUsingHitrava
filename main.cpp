#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;

std::vector<std::string> file_list(std::string path) {
    auto files = std::vector<std::string>();
    for (const auto & entry : fs::directory_iterator(path)){
        auto f_path = entry.path().parent_path().string() + "/" + entry.path().filename().string();
        files.push_back(f_path);
    }
    return  files;
}

void exec_cmd(std::string exec, std::string path) {
    std::string str = exec;
    str = str + " --file " + path;
    system(reinterpret_cast<const char *>(str.c_str()));
}

void move_files(std::string to_move_path) {
    auto current_path = fs::current_path().string() + "\\output";
    for (const auto & entry : fs::directory_iterator(current_path)){
        auto file_path = entry.path().filename().string();
        fs::rename(entry.path(), to_move_path + "/" + file_path);
    }
}

int main() {
    auto file_patches = file_list("C:/Users/Dima/Downloads");
    auto path_to_exec = "C:/Users/Dima/Documents/Main/TCX-Converter/Huawei-TCX-Converter.py";
    for (auto f_path : file_patches) {
        if (f_path.find("HiTrack") != std::string::npos) {
            exec_cmd(path_to_exec, f_path);
        }
    }
    move_files("C:/Users/Dima/Downloads");
    return 0;
}
