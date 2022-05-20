#include <fstream>
#include <iostream>
#include <string.h>

using namespace std;

void getFileSize(fstream& file, int& size)
{
    file.clear();
    file.seekg (0, ios::beg);
    char ch;
    while(1)
    {
        file.get(ch);
        if(file.eof())
        {
            return;
        }
        size++;
    }
}

void storeData(char* target, fstream &file , int start, int end)
{
    file.clear();
    file.seekg (0, ios::beg);
    char ch;
    int i = start;
    while(i < end)
    {
        file.get(ch);
        if(file.eof())
        {
            return;
        }
        target[i] = ch;
        i++;
    }
}

void copyData(fstream& file, char* data, int size)
{
    for (int i = 0; i < size; i++)
    {
        file.put(data[i]);
    }
    
}

void displayFileData(fstream &file)
{
    file.clear();
    file.seekg (0, ios::beg);
    char ch;
    while (1)
    {
        file.get(ch);
        if(file.eof())
        {
            return;
        }
        cout << ch;
    }
    
}

int calcTotalSize(int *fileSizes, int totalFiles)
{
    int totalSize = 0;
    for (int i = 0; i < totalFiles; i++)
    {
        totalSize += fileSizes[i];
    }
    return totalSize;
}


int main()
{
    fstream finalFile;
    string finalFileName;
    int total_characters_in_all_files = 0;
    int totalFiles = 0, curr_File_char_value = 0;
    
    cout << "Enter the number of files to copy data from : ";
    cin >> totalFiles;
    
    string files[totalFiles];

    cout << "Enter names of files along with .txt extension (Example : file1.txt) \n";
    for (int i = 0; i < totalFiles; i++)
    {
        getline(cin >> ws, files[i]);
    }

    cout << "Enter the name of file where you want to copy all the files (add .txt extension in the end) : ";
    cin >> finalFileName;


    fstream *in_files = new fstream[totalFiles];
    int *in_sizes = new int[totalFiles];


    for (int i = 0; i < totalFiles; i++)
    {
        in_files[i].open(files[i], ios::in);
        if(!in_files[i])
        {
            cout << "\n" << "[ERROR] : No file found named \"" << files[i] << "\"" << endl;
            cout << "Have you entered the file name correctly ? \n";
            return 1;
        }
        in_sizes[i] = 0;
    }
    
    for (int i = 0; i < totalFiles; i++)
    {
        getFileSize(in_files[i], in_sizes[i]);
    }

    total_characters_in_all_files = calcTotalSize(in_sizes, totalFiles);
    
    char *data = new char[total_characters_in_all_files];


    for (int i = 0; i < totalFiles; i++)
    {
        storeData(data, in_files[i], curr_File_char_value, curr_File_char_value + in_sizes[i]);
        curr_File_char_value += in_sizes[i];
    }
    
    finalFile.open(finalFileName, ios::out);

    copyData(finalFile, data, total_characters_in_all_files);
    finalFile.close();

    cout << "\n------------------------------------Final File Data--------------------------- \n";

    finalFile.open(finalFileName, ios::in);
    displayFileData(finalFile);

    for (int i = 0; i < totalFiles; i++)
    {
        in_files[i].close();
    }
    finalFile.close();

    delete []in_files;
    delete []in_sizes;
    return 0;
}