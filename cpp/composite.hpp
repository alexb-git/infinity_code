/****************************************************************************
** Filename:    - composite.hpp
** Code Author: - Alex B
** Mail:        - aether.alex@gmail.com
** Purpose:     - composite design pattern
** Date:        - 13/2/2018
** Version:     - 1
*****************************************************************************/


/**********************************************************
Filename : composite.hpp
Date     : 13/02/18
purpose  : Header file of composite design patern
Design Patern: Compsite
Version: 7
**********************************************************/
#ifndef __COMPOSITE_HPP__
#define __COMPOSITE_HPP__

#include <tr1/memory>   // shared_ptr
#include <string>
#include <vector>

namespace ilrd
{

/*===========  FileComponent class - abstract file class (Interface) ========*/
class FileComponent
{
public:
    explicit FileComponent(const std::string& file_name) throw (std::exception);
    virtual void Print(size_t depth = 0) const = 0;
    virtual ~FileComponent() = 0;

protected:
    const std::string m_file_name;


private:
  FileComponent(const FileComponent& obj);            /* disabled */
  FileComponent&operator=(const FileComponent& obj);  /* disabled */
};

/*==============================  File class  ==============================*/
class File : public FileComponent
{
public:
    explicit File(const std::string& file_name);
    virtual ~File();
    virtual void Print(size_t depth = 0) const;

    /* copy Ctor and '=' operator are disabled by inheritance */
};

/*===========================  Directory class  =============================*/
class Directory: public FileComponent
{
public:
    explicit Directory(const std::string& path);
    virtual ~Directory();
    virtual void Print(size_t depth = 0) const;

protected:
    std::vector< std::tr1::shared_ptr<FileComponent> > m_files;

private:
    void InitVec(const std::string& path);
    /* copy Ctor and '=' operator are disabled by inheritance */
};

} // namespace ilrd

#endif /*__COMPOSITE_HPP__ */
