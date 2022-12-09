#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

const int SIZE_THRESHOLD = 100000;
const int STORAGE_SPACE = 70000000;
const int SPACE_FOR_UPDATE = 30000000;

struct File {
  bool _is_directory = false;
  std::string _name;
  int _size;
  File* _parent = nullptr;
  std::vector<File*> _files;
};

void CalculateDirectorySizes(File* directory) {
  for (File* f : directory->_files) {
    if (f->_is_directory) {
      CalculateDirectorySizes(f);
    }
    directory->_size += f->_size;
  }
}

int size = 0;

void CalculateSizeThresholdRec(File* directory) {
  if (directory->_size <= SIZE_THRESHOLD) {
    size += directory->_size;
  }

  for (File* f : directory->_files) {
    if (f->_is_directory) {
      CalculateSizeThresholdRec(f);
    }
  }
}

std::vector<File*> big_directories;

void GetBigDirectories(File* directory, int needed_space) {
  for (File* f : directory->_files) {
    if (f->_is_directory) {
      GetBigDirectories(f, needed_space);
    }
  }

  if (directory->_size >= needed_space) {
    big_directories.push_back(directory);
  }
}

int main() {
  size = 0;

  std::ifstream input("../../input.txt");

  std::string line;
  std::string word;
  std::string command;

  File* file_system = new File();
  file_system->_name = "/";
  file_system->_parent = file_system;

  File* current_folder = file_system;

  std::vector<std::string>
      line_contents;

  while (std::getline(input, line)) {
    // Initialize
    std::stringstream line_stream(line);
    line_contents.clear();

    while (std::getline(line_stream, word, ' ')) {
      line_contents.push_back(word);
    }

    // extract commands
    if (line_contents.at(0) == "$") {
      command = line_contents.at(1);
    }

    if (command == "cd") {
      if (line_contents.at(2) == "..") {
        current_folder = current_folder->_parent != nullptr ? current_folder->_parent : current_folder;
      }

      for (File* f : current_folder->_files) {
        if (f->_name == line_contents.at(2)) {
          current_folder = f;
        }
      }

      continue;
    }

    // populate fake filesystem
    if (command == "ls") {
      File* new_file = new File();
      if (line_contents.at(0) == "$") {
        continue;
      } else if (line_contents.at(0) == "dir") {
        new_file->_name = line_contents.at(1);
        new_file->_is_directory = true;
        new_file->_parent = current_folder;
        current_folder->_files.push_back(new_file);
      } else {
        new_file->_name = line_contents.at(1);
        new_file->_size = std::stoi(line_contents.at(0));
        new_file->_parent = current_folder;
        current_folder->_files.push_back(new_file);
      }

      continue;
    }
  }

  CalculateDirectorySizes(file_system);
  CalculateSizeThresholdRec(file_system);

  std::cout << "size of filesystem: " << file_system->_size << std::endl;
  std::cout << "size of directories that are under or equal to 100000: " << size << std::endl;

  int free_space = STORAGE_SPACE - file_system->_size;
  std::cout << "free space: " << free_space << std::endl;

  int needed_space = SPACE_FOR_UPDATE - free_space;
  std::cout << "needed space for update: " << needed_space << std::endl;

  GetBigDirectories(file_system, needed_space);

  File* smallest_option_to_delete = nullptr;
  // int smallest_size = STORAGE_SPACE;

  for (File* file : big_directories) {
    if (smallest_option_to_delete == nullptr) {
      smallest_option_to_delete = file;
    }

    if (file->_size < smallest_option_to_delete->_size) {
      // smallest_size = file->_size;
      smallest_option_to_delete = file;
    }
  }

  std::cout << "Size of directory to be deleted: " << smallest_option_to_delete->_size << std::endl;
}