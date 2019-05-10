//
// init_menu.cpp for  in /home/doremi/rendu/cpp/cpp_arcade
//
// Made by Guillaume
// Login   <doremi@epitech.net>
//
// Started on  Thu Mar 30 12:41:06 2017 Guillaume
// Last update Thu Mar 30 18:03:55 2017 Guillaume
//

#include "init_menu.hpp"

init_menu::init_menu()
{

}

init_menu::~init_menu()
{

}

void	init_menu::get_hscore(info_lib *elem)
{
  int max_score = -1;
  int current_score = 0;
  std::string max_name = "None";
  std::string current_name = "";
  std::string buff = "";
  std::string file_name = "." + elem->name + ".score";
  std::string line = "";
  std::ifstream file;
  std::size_t pos = 0;

  file.open (file_name.c_str());
  while(getline(file,line))
  {
    pos = line.find(" : ");
    current_name = line.substr(0, pos);
    buff = line.substr(pos + 3);
    current_score = atoi(buff.c_str());
    if (current_score > max_score)
    {
      max_score = current_score;
      max_name = current_name;
    }
  }
  elem->hscore = max_score;
  elem->hscore_name = max_name;
  if (elem->hscore == -1)
    elem->hscore = 0;  
}

int    my_strlen(char *str)
{
  int   i = 0;

  while (str[i] != '\0')
    i++;
  return (i);
}

int    is_a_libso_file(char *name)
{
  int a = 0;
  if (my_strlen(name) > 6)
    {
      if (name[0] == 'l' && name[1] == 'i' && name[2] == 'b')
        {
          a = my_strlen(name) - 1;
          if (name[a] == 'o' && name[a - 1] == 's' && name[a - 2] == '.')
          {
            return (1);
          }
          return (0);
        }
      return (0);
    }
    return (0);
}

std::string   get_name(char *str)
{
  std::string res = "";
  int i = 11;
  

  while (str[i] != '.' && str[i] != '\0')
  {
    res = res + str[i];
    i++;
  }
  return (res);
}

std::vector<info_lib>	init_menu::get_all_libs()
{
  std::vector<info_lib>	libs;
  info_lib		elem;
  struct dirent *res;
  DIR           *dir;
  int           i = 0;
  char		*dossier = (char*)"graph";

  dir = this->_lib.my_opendir(dossier);
  while ((res = this->_lib.my_readdir(dir)) != NULL)
  {
    if (is_a_libso_file(res->d_name) == 1)
    {
      std::string path(res->d_name);
      elem.path = "graph/" + path;
      elem.name = get_name(res->d_name);
      elem.hscore_name = "";
      elem.pos = i;
      elem.hscore = 0;
      libs.push_back(elem);
      i++;
    }
  }
  this->_lib.my_closedir(dir);
  return (libs);
}

std::vector<info_lib>	init_menu::get_all_games()
{
  std::vector<info_lib>	libs;
  info_lib		elem;
  struct dirent *res;
  DIR           *dir;
  int           i = 0;
  char		*dossier = (char*)"games";

  dir = this->_lib.my_opendir(dossier);
  while ((res = this->_lib.my_readdir(dir)) != NULL)
  {
    if (is_a_libso_file(res->d_name) == 1)
    {
      std::string path(res->d_name);
      elem.path = "games/" + path;
      elem.name = get_name(res->d_name);
      elem.hscore_name = "";
      elem.pos = i;
      get_hscore(&elem);
      libs.push_back(elem);
      i++;
    }
  }
  return (libs);  
}
