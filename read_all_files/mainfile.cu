// files you need to include, do not forget to include the -lboost_filesystem and -lboost_system libraries otherwise you will get quite some errors/complaints during the compilation
#include <boost/filesystem.hpp>
using namespace boost::filesystem;

void readFilenamesBoost(vector<string> &filenames, const string &folder)
{
    path directory(folder);
    directory_iterator itr(directory), end_itr;

    string current_file = itr->path().string();

    for(;itr != end_itr; ++itr)
    {
// If it's not a directory, list it. If you want to list directories too, just remove this check.
       if (is_regular_file(itr->path()))
       {
       // assign current file name to current_file and echo it out to the console.
//            string full_file_name = itr->path().string(); // returns full path
            string filename = itr->path().filename().string(); // returns just filename
            filenames.push_back(filename);
       }
    }
}

int main()
{
    string folder = "/documents/images/";
    vector<string> filenames;

    readFilenamesBoost(filenames, folder);

    for(size_t i = 0; i < filenames.size(); ++i)
    {
        Mat src = imread(folder + filenames[i]);

        if(!src.data)
            cerr << "Problem loading image!!!" << endl;

        /* do whatever you want with your images here */
    }
}