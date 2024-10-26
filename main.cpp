#include<iostream>
#include<vector>
#include<unistd.h>
#include<filesystem>
#include<fstream>

using namespace std;

string return_current_path() {
  char cwd[256];

  getcwd(cwd, sizeof(cwd) - 1);

  return string(cwd);
}

void setup_args(vector<string> &args, int argc, char *argv[]) {
  for(int i = 0; i!=argc; i++) {
    if(i!=0) { args.push_back(argv[i]); };
  }
}

string create_dir(string path) {
  filesystem::path dir = path;

  filesystem::create_directory(dir);
  cout << "Setting up (" << path << ")" << endl; 

  return path;
}

void create_file(string path) {
  ofstream file(path);
  file << "// Created file by polymorqhism :)\n\n#include<iostream>\n\nusing namespace std;\n\nint main() {\n// code here\n}\n";
  cout << "Created " << path << endl;
}

int main(int argc, char *argv[]) {
  vector<string> args;
  string upath;

  setup_args(args, argc, argv);

  string project_name = args[0];

  cout << "Path? Type NULL if current: ";

  cin >> upath;

  if(cin.fail()) { cout << "Failed to read"; return 0; };

  string current_path = return_current_path();

  if(upath != "NULL") {
    current_path = upath;
  }

  string main_folder = current_path + "/" + project_name;

  cout << main_folder;

  string created_main = create_dir(main_folder) + "/src";

  string created_src = create_dir(created_main);

  create_file(created_src + "/main.cpp");

  for(int i = 1; i!=argc; i++) {
    create_file(created_src + "/" + args[i]);
  }

  cout << "SETUP COMPLETE :D" << endl;
  
} 
