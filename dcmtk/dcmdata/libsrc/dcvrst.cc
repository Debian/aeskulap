/*
 *
 *  Copyright (C) 1994-2005, OFFIS
 *
 *  This software and supporting documentation were developed by
 *
 *    Kuratorium OFFIS e.V.
 *    Healthcare Information and Communication Systems
 *    Escherweg 2
 *    D-26121 Oldenburg, Germany
 *
 *  THIS SOFTWARE IS MADE AVAILABLE,  AS IS,  AND OFFIS MAKES NO  WARRANTY
 *  REGARDING  THE  SOFTWARE,  ITS  PERFORMANCE,  ITS  MERCHANTABILITY  OR
 *  FITNESS FOR ANY PARTICULAR USE, FREEDOM FROM ANY COMPUTER DISEASES  OR
 *  ITS CONFORMITY TO ANY SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND
 *  PERFORMANCE OF THE SOFTWARE IS WITH THE USER.
 *
 *  Module:  dcmdata
 *
 *  Author:  Gerd Ehlers
 *
 *  Purpose: Implementation of class DcmShortText
 *
 *  Last Update:      $Author: braindead $
 *  Update Date:      $Date: 2007/04/24 09:53:26 $
 *  CVS/RCS Revision: $Revision: 1.2 $
 *  Status:           $State: Exp $
 *
 *  CVS/RCS Log at end of file
 *
 */


#include "dcmtk/config/osconfig.h"    /* make sure OS specific configuration is included first */

#include "dcmtk/dcmdata/dcvrst.h"


// ********************************


DcmShortText::DcmShortText(const DcmTag &tag,
                           const Uint32 len)
  : DcmCharString(tag, len)
{
    maxLength = 1024;
}


DcmShortText::DcmShortText(const DcmShortText &old)
  : DcmCharString(old)
{
}


DcmShortText::~DcmShortText()
{
}


DcmShortText &DcmShortText::operator=(const DcmShortText &obj)
{
    DcmCharString::operator=(obj);
    return *this;
}


// ********************************


DcmEVR DcmShortText::ident() const
{
    return EVR_ST;
}


unsigned long DcmShortText::getVM()
{
    /* value multiplicity is 1 for non-empty string, 0 otherwise */
    return (getRealLength() > 0) ? 1 : 0;
}


// ********************************


OFCondition DcmShortText::getOFString(OFString &stringVal,
                                      const unsigned long /*pos*/,
                                      OFBool normalize)
{
    /* treat backslash as a normal character */
    return getOFStringArray(stringVal, normalize);
}


OFCondition DcmShortText::getOFStringArray(OFString &stringVal,
                                           OFBool normalize)
{
    /* get string value without handling the "\" as a delimiter */
    OFCondition l_error = getStringValue(stringVal);
    if (l_error.good() && normalize)
        normalizeString(stringVal, !MULTIPART, !DELETE_LEADING, DELETE_TRAILING);
    return l_error;
}


/*
** CVS/RCS Log:
** $Log: dcvrst.cc,v $
** Revision 1.2  2007/04/24 09:53:26  braindead
** - updated DCMTK to version 3.5.4
** - merged Gianluca's WIN32 changes
**
** Revision 1.1.1.1  2006/07/19 09:16:40  pipelka
** - imported dcmtk354 sources
**
**
** Revision 1.15  2005/12/08 15:42:04  meichel
** Changed include path schema for all DCMTK header files
**
** Revision 1.14  2004/01/16 13:47:37  joergr
** Removed acknowledgements with e-mail addresses from CVS log.
** Added missing #include "osconfig.h".
**
** Revision 1.13  2002/12/06 13:05:52  joergr
** Fixed bug in Unlimited Text (UT) class: the backslash character was treated
** as a component separator which is wrong according to the DICOM standard.
** The same bug was found in class Long Text (LT) and Short Text (ST).  Also
** changed the behaviour of the getVM() method; now returns 1 only in case of
** non-empty string values.
** Made source code formatting more consistent with other modules/files.
**
** Revision 1.12  2002/04/25 10:33:40  joergr
** Added/modified getOFStringArray() implementation.
**
** Revision 1.11  2001/09/25 17:20:01  meichel
** Adapted dcmdata to class OFCondition
**
** Revision 1.10  2001/06/01 15:49:20  meichel
** Updated copyright header
**
** Revision 1.9  2000/03/08 16:26:51  meichel
** Updated copyright header.
**
** Revision 1.8  1999/03/31 09:25:59  meichel
** Updated copyright header in module dcmdata
**
** Revision 1.7  1998/11/12 16:48:29  meichel
** Implemented operator= for all classes derived from DcmObject.
**
** Revision 1.6  1997/08/29 13:11:49  andreas
** Corrected Bug in getOFStringArray Implementation
**
** Revision 1.5  1997/08/29 08:33:01  andreas
** - Added methods getOFString and getOFStringArray for all
**   string VRs. These methods are able to normalise the value, i. e.
**   to remove leading and trailing spaces. This will be done only if
**   it is described in the standard that these spaces are not relevant.
**   These methods do not test the strings for conformance, this means
**   especially that they do not delete spaces where they are not allowed!
**   getOFStringArray returns the string with all its parts separated by \
**   and getOFString returns only one value of the string.
**   CAUTION: Currently getString returns a string with trailing
**   spaces removed (if dcmEnableAutomaticInputDataCorrection == OFTrue) and
**   truncates the original string (since it is not copied!). If you rely on this
**   behaviour please change your application now.
**   Future changes will ensure that getString returns the original
**   string from the DICOM object (NULL terminated) inclusive padding.
**   Currently, if you call getOF... before calling getString without
**   normalisation, you can get the original string read from the DICOM object.
**
** Revision 1.4  1997/07/03 15:10:19  andreas
** - removed debugging functions Bdebug() and Edebug() since
**   they write a static array and are not very useful at all.
**   Cdebug and Vdebug are merged since they have the same semantics.
**   The debugging functions in dcmdata changed their interfaces
**   (see dcmdata/include/dcdebug.h)
**
** Revision 1.3  1996/01/05 13:27:54  andreas
** - changed to support new streaming facilities
** - unique read/write methods for file and block transfer
** - more cleanups
**
*/
