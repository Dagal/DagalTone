#ifndef _WALLSOCKET_HPP_
#define _WALLSOCKET_HPP_

#include <glibmm.h>

class WallSocket
{
  // Methods
public:
  WallSocket();
  virtual ~WallSocket();

  // Variables
private:
  Glib::ustring mName;
  
};

#endif // _WALLSOCKET_HPP_
