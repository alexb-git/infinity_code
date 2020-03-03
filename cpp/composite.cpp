/****************************************************************************
** Filename:    - composite.hpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - composite design pattern (implemintation)
** Date:        - 13/2/2018
** Version:     - 1
*****************************************************************************/
#include "composite.hpp"

#include <dirent.h>   /* struct dirent, opendir, readdir */
#include <iostream>   /* cout, endl */
#include <cstring>    /* strcmp */
/****************************************************************************
    Helpful colors
*****************************************************************************/
#define YLL	 "\x1b[93m"
#define GRE	 "\x1b[92m"
#define RED	 "\x1b[91m"
#define WHI	 "\x1B[37m"
#define CYA	 "\x1B[36m"
#define BLU	 "\x1B[34m"
#define YEL	 "\x1b[33m"
#define RES	 "\x1b[0m"
#define BLD  "\x1B[1m"
#define UDL  "\x1b[4m"
/****************************************************************************/

namespace ilrd
{

static void PrintEntry( const char        *color  ,
                        const char        *prefix ,
                        const std::string &str    ,
                        size_t             depth  )
{
    while ( depth-- )
    {
        std::cout << YLL "|--" RES;
    }

    /*  count only the file name (without full path)
        e.x: 'svn/Proj/src/cpp/cpp2c.cpp' => 'cpp2c.cpp' */
    size_t found = str.rfind("/") + 1;

    std::cout
    << WHI << prefix        /* print prefix */
    << color << &str[found] /* file name without full path */
    << RES << std::endl;
}

/****************************************************************************
    FileComponent
*****************************************************************************/
FileComponent::FileComponent(const std::string& file_name)
throw (std::exception):
                        m_file_name(file_name)
{}

void FileComponent::Print(size_t depth) const
{
    std::cout << BLU << m_file_name << RES << std::endl;
}


FileComponent::~FileComponent()
{}

/****************************************************************************
    File
*****************************************************************************/
File::File(const std::string& file_name) : FileComponent(file_name)
{}

void File::Print(size_t depth) const
{
    const char *prefix = "> ";

    PrintEntry(BLU, prefix, m_file_name, depth);
}

File::~File()
{}

/****************************************************************************
    Directory
*****************************************************************************/
Directory::Directory(const std::string& path) :
    FileComponent(path)
{
    InitVec(path);
}

void Directory::InitVec(const std::string& path)
{
    DIR *dir  = opendir(path.c_str());

    if( NULL == dir )
    {
        /* dir was unable to open, access denided */
        m_file_name + " {access denided}";
        closedir(dir);
        return;
    }

    try /* may fail: (1) mem. allocation (2) readdir */
    {
        struct dirent *ent;

        /* print all the files and directories within directory */
        while ((ent = readdir(dir)) != NULL)
        {
            /* append file name to current path */
            std::string str(m_file_name + "/" + ent->d_name);

            /* if (1) is a directory
                  (2) not itself (else endless loop)
                  (3) not parent dir (else endless loop) */
            if (    DT_DIR == ent->d_type
                 && strcmp((ent->d_name), ".") != 0
                 && strcmp((ent->d_name),"..") != 0 )
            {
                std::tr1::shared_ptr<FileComponent>
                        ptr(new Directory(str));

                m_files.push_back(ptr);
            }
            else /* not a directory */
            {
                std::tr1::shared_ptr<FileComponent> ptr(new File(str));
                m_files.push_back(ptr);
            }

            // std::cout << RED "pushed: " << str << RES << std::endl;
        }

    } /* end of try block */

    catch (std::exception &e)
	{
        /* close directory and re-throw the error for user to handle */
		std::cout << RED << "ERROR had occurred - " << e.what() << std::endl;
	    closedir(dir);
		throw std::exception();
	}

    closedir (dir);
}

void Directory::Print(size_t depth) const
{
    const char *prefix = "";

    /* print directory and some info */
    PrintEntry(RED, prefix, m_file_name, depth);
    std::cout << "\t(# of entries = " << m_files.size() << ")" << std::endl;

    /* print directory content */
    size_t v_size = m_files.size();
    for ( size_t i = 0 ; i < v_size ; ++i )
    {
        m_files[i]->Print(depth + 1);
    }
}

Directory::~Directory()
{}


}
