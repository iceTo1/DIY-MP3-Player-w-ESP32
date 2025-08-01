#include "include/utils.h"

String adjustFileName(String& fileName)
{
  // Adjust the filename to begin with "/"
  if (!fileName.startsWith("/"))
  {
    fileName = "/" + fileName;
  }

  // Return with c string to pass to SD functions
  return fileName;
}