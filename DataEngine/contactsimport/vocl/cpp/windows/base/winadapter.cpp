/*
 * Funambol is a mobile platform developed by Funambol, Inc. 
 * Copyright (C) 2003 - 2007 Funambol, Inc.
 * 
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Affero General Public License version 3 as published by
 * the Free Software Foundation with the addition of the following permission 
 * added to Section 15 as permitted in Section 7(a): FOR ANY PART OF THE COVERED
 * WORK IN WHICH THE COPYRIGHT IS OWNED BY FUNAMBOL, FUNAMBOL DISCLAIMS THE 
 * WARRANTY OF NON INFRINGEMENT  OF THIRD PARTY RIGHTS.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 * 
 * You should have received a copy of the GNU Affero General Public License 
 * along with this program; if not, see http://www.gnu.org/licenses or write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA.
 * 
 * You can contact Funambol, Inc. headquarters at 643 Bair Island Road, Suite 
 * 305, Redwood City, CA 94063, USA, or at email address info@funambol.com.
 * 
 * The interactive user interfaces in modified source and object code versions
 * of this program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU Affero General Public License version 3.
 * 
 * In accordance with Section 7(b) of the GNU Affero General Public License
 * version 3, these Appropriate Legal Notices must retain the display of the
 * "Powered by Funambol" logo. If the display of the logo is not reasonably 
 * feasible for technical reasons, the Appropriate Legal Notices must display
 * the words "Powered by Funambol".
 */
#include "stdafx.h"

#include <stdio.h>
#include "base/Log.h"
#include "base/util/utils.h"
#include "base/globalsdef.h"
#include <ShlObj.h>
#include <time.h>

#ifdef _WIN32_WCE
#include <crtdefs.h>        // for __time64_t
#include <altcecrt.h>       // for _gmtime64_s()
#endif

#if defined(WIN32) && !defined(_WIN32_WCE)
#include <sys/stat.h>
#endif

BEGIN_NAMESPACE

struct Codepage {
    const char *name;
    int  codepage_id;
};

static Codepage encodings[] = {
    { "_iso-2022-jp", 50221 },
    { "_iso-2022-jp$sio", 50222 },
    { "ansi_x3.4-1968", 1252 },
    { "ansi_x3.4-1986", 1252 },
    { "arabic", 28596 },
    { "ascii", 1252 },
    { "asmo-708", 708 },
    { "big5", 950 },
    { "chinese", 936 },
    { "cn-big5", 950 },
    { "cn-gb", 936 },
    { "codepage437", 437 },
    { "cp1026", 1026 },
    { "cp1256", 1256 },
    { "cp367", 1252 },
    { "cp437", 437 },
    { "cp500", 775 },
    { "cp819", 1252 },
    { "cp852", 852 },
    { "cp866", 866 },
    { "cp870", 870 },
    { "csascii", 1252 },
    { "csbig5", 950 },
    { "cseuckr", 51949 },
    { "cseucpkdfmtjapanese", 51932 },
    { "csgb2312", 936 },
    { "csgb231280", 936 },
    { "csiso", 28591 },
    { "csiso2022jp", 50221 },
    { "csiso2022kr", 50225 },
    { "csiso58gb231280", 936 },
    { "csisolatin2", 28592 },
    { "csisolatin4", 28594 },
    { "csisolatin5", 28595 },
    { "csisolatinarabic", 28596 },
    { "csisolatincyrillic", 28595 },
    { "csisolatingreek", 28597 },
    { "csisolatinhebrew", 28598 },
    { "cskoi8r", 20866 },
    { "csksc56011987", 949 },
    { "cspc8", 437 },
    { "csshiftjis", 932 },
    { "csunicode11utf7", 65000 },
    { "cswindows31j", 932 },
    { "cyrillic", 28595 },
    { "dos-720", 720 },
    { "dos-862", 862 },
    { "dos-874", 874 },
    { "ebcdic-cp-us", 37 },
    { "ecma-114", 28596 },
    { "ecma-118", 28597 },
    { "elot_928", 28597 },
    { "euc-cn", 51936 },
    { "euc-jp", 51932 },
    { "euc-kr", 51949 },
    { "gb2312", 936 },
    { "gb2312-80", 936 },
    { "gb231280", 936 },
    { "gb_2312-80", 936 },
    { "gbk", 936 },
    { "greek", 28597 },
    { "greek8", 28597 },
    { "hebrew", 28598 },
    { "hz-gb-2312", 52936 },
    { "ibm367", 1252 },
    { "ibm437", 437 },
    { "ibm737", 737 },
    { "ibm775", 775 },
    { "ibm819", 1252 },
    { "ibm850", 850 },
    { "ibm852", 852 },
    { "ibm857", 857 },
    { "ibm861", 861 },
    { "ibm866", 866 },
    { "ibm869", 869 },
    { "iso-2022-jp", 50222 },
    { "iso-2022-kr", 50225 },
    { "iso-8859-1", 1252 },
    { "iso-8859-11", 874 },
    { "iso-8859-15", 28605 },
    { "iso-8859-2", 28592 },
    { "iso-8859-3", 28593 },
    { "iso-8859-4", 28594 },
    { "iso-8859-5", 28595 },
    { "iso-8859-6", 28596 },
    { "iso-8859-7", 28597 },
    { "iso-8859-8", 1255 },
    { "iso-8859-8-i", 38598 },
    { "iso-8859-9", 1254 },
    { "iso-ir-100", 1252 },
    { "iso-ir-101", 28592 },
    { "iso-ir-109", 28593 },
    { "iso-ir-110", 28594 },
    { "iso-ir-126", 28597 },
    { "iso-ir-127", 28596 },
    { "iso-ir-138", 28598 },
    { "iso-ir-144", 28595 },
    { "iso-ir-148", 1254 },
    { "iso-ir-149", 949 },
    { "iso-ir-58", 936 },
    { "iso-ir-6", 1252 },
    { "iso-ir-6us", 20127 },
    { "iso646-us", 1252 },
    { "iso8859-1", 1252 },
    { "iso8859-2", 28592 },
    { "iso_646.irv:1991", 1252 },
    { "iso_8859-1", 1252 },
    { "iso_8859-15", 28605 },
    { "iso_8859-1:1987", 1252 },
    { "iso_8859-2", 28592 },
    { "iso_8859-2:1987", 28592 },
    { "iso_8859-3", 28593 },
    { "iso_8859-3:1988", 28593 },
    { "iso_8859-4", 28594 },
    { "iso_8859-4:1988", 28594 },
    { "iso_8859-5", 28595 },
    { "iso_8859-5:1988", 28595 },
    { "iso_8859-6", 28596 },
    { "iso_8859-6:1987", 28596 },
    { "iso_8859-7", 28597 },
    { "iso_8859-7:1987", 28597 },
    { "iso_8859-8", 28598 },
    { "iso_8859-8-i", 1255 },
    { "iso_8859-8:1988", 28598 },
    { "iso_8859-9", 1254 },
    { "iso_8859-9:1989", 1254 },
    { "johab", 1361 },
    { "koi", 20866 },
    { "koi8", 20866 },
    { "koi8-r", 20866 },
    { "koi8-ru", 21866 },
    { "koi8-u", 21866 },
    { "koi8r", 20866 },
    { "korean", 949 },
    { "ks_c_5601", 949 },
    { "ks_c_5601-1987", 949 },
    { "ks_c_5601-1989", 949 },
    { "ks_c_5601_1987", 949 },
    { "ksc5601", 949 },
    { "ksc_5601", 949 },
    { "l1", 28591 },
    { "l2", 28592 },
    { "l3", 28593 },
    { "l4", 28594 },
    { "l5", 28599 },
    { "l9", 28605 },
    { "latin1", 1252 },
    { "latin2", 28592 },
    { "latin3", 28593 },
    { "latin4", 28594 },
    { "latin5", 1254 },
    { "latin9", 28605 },
    { "logical", 38598 },
    { "macintosh", 10000 },
    { "ms_kanji", 932 },
    { "shift-jis", 932 },
    { "shift_jis", 932 },
    { "tis-620", 874 },
    { "unicode", 1200 },
    { "unicode-1-1-utf-7", 65000 },
    { "unicode-1-1-utf-8", 65001 },
    { "unicode-2-0-utf-8", 65001 },
    { "unicodefffe", 1201 },
    { "us", 1252 },
    { "us-ascii", 1252 },
    { "utf-16", 1200 },
    { "utf-7", 65000 },
    { "utf-8", 65001 },
    { "visual", 1255 },
    { "windows-1250", 1250 },
    { "windows-1251", 1251 },
    { "windows-1252", 1252 },
    { "windows-1253", 1253 },
    { "windows-1254", 1254 },
    { "windows-1255", 1255 },
    { "windows-1256", 1256 },
    { "windows-1257", 1257 },
    { "windows-1258", 1258 },
    { "windows-874", 874 },
    { "x-ansi", 1252 },
    { "x-chinese-cns", 20000 },
    { "x-chinese-eten", 20002 },
    { "x-cp1250", 1250 },
    { "x-cp1251", 1251 },
    { "x-ebcdic-arabic", 20420 },
    { "x-ebcdic-cp-us-euro", 1140 },
    { "x-ebcdic-cyrillicrussian", 20880 },
    { "x-ebcdic-cyrillicserbianbulgarian", 21025 },
    { "x-ebcdic-denmarknorway", 20277 },
    { "x-ebcdic-denmarknorway-euro", 1142 },
    { "x-ebcdic-finlandsweden", 20278 },
    { "x-ebcdic-finlandsweden-euro", 1143 },
    { "x-ebcdic-france", 1143 },
    { "x-ebcdic-france-euro", 1147 },
    { "x-ebcdic-germany", 20273 },
    { "x-ebcdic-germany-euro", 1141 },
    { "x-ebcdic-greek", 20423 },
    { "x-ebcdic-greekmodern", 875 },
    { "x-ebcdic-hebrew", 20424 },
    { "x-ebcdic-icelandic", 20871 },
    { "x-ebcdic-icelandic-euro", 1149 },
    { "x-ebcdic-international-euro", 1148 },
    { "x-ebcdic-italy", 20280 },
    { "x-ebcdic-italy-euro", 1144 },
    { "x-ebcdic-japaneseandjapaneselatin", 50939 },
    { "x-ebcdic-japaneseandkana", 50930 },
    { "x-ebcdic-japaneseanduscanada", 50931 },
    { "x-ebcdic-japanesekatakana", 20290 },
    { "x-ebcdic-koreanandkoreanextended", 50933 },
    { "x-ebcdic-koreanextended", 20833 },
    { "x-ebcdic-simplifiedchinese", 50935 },
    { "x-ebcdic-spain", 20284 },
    { "x-ebcdic-spain-euro", 1145 },
    { "x-ebcdic-thai", 20838 },
    { "x-ebcdic-traditionalchinese", 50937 },
    { "x-ebcdic-turkish", 20905 },
    { "x-ebcdic-uk", 20285 },
    { "x-ebcdic-uk-euro", 1146 },
    { "x-euc", 51932 },
    { "x-euc-cn", 51936 },
    { "x-euc-jp", 51932 },
    { "x-europa", 29001 },
    { "x-ia5", 20105 },
    { "x-ia5-german", 20106 },
    { "x-ia5-norwegian", 20108 },
    { "x-ia5-swedish", 20107 },
    { "x-iscii-as", 57006 },
    { "x-iscii-be", 57003 },
    { "x-iscii-de", 57002 },
    { "x-iscii-gu", 57010 },
    { "x-iscii-ka", 57008 },
    { "x-iscii-ma", 57009 },
    { "x-iscii-or", 57007 },
    { "x-iscii-pa", 57011 },
    { "x-iscii-ta", 57004 },
    { "x-iscii-te", 57005 },
    { "x-mac-arabic", 10004 },
    { "x-mac-ce", 10029 },
    { "x-mac-chinesesimp", 10008 },
    { "x-mac-chinesetrad", 10002 },
    { "x-mac-cyrillic", 10007 },
    { "x-mac-greek", 10006 },
    { "x-mac-hebrew", 10005 },
    { "x-mac-icelandic", 10079 },
    { "x-mac-japanese", 10001 },
    { "x-mac-korean", 10003 },
    { "x-mac-turkish", 10081 },
    { "x-ms-cp932", 932 },
    { "x-sjis", 932 },
    { "x-unicode-2-0-utf-7", 65000 },
    { "x-unicode-2-0-utf-8", 65001 },
    { "x-x-big5", 950 },
    { NULL, 0 }
};


/*
 * Return a filename composed by the system temp dir and the name given
 * in input. If the file exists, try to add a digit 0-9.
 * If this fails too, return NULL (there's must be something wrong in
 * the calling program)
 *
 * @param name - a file name, without path
 * @return - a full pathname, allocated with new[], or NULL on error
 */
char *mkTempFileName(const char *name)
{
    WCHAR tmpPath[64];
    WCHAR tmpFileName[MAX_PATH];  // System constants for the path

    GetTempPath(64, tmpPath);
    int ret = GetTempFileName(tmpPath, L"fun", 0, tmpFileName);

    if (ret == 0) { // function GetTempFileName fails
        LOG.error("mkTempFileName: error in GetTempFileName");
        return 0;
    }
    return toMultibyte(tmpFileName);
}

// check the presence of a file
bool fileExists(const char *pathname) {
    FILE *fh = fileOpen(pathname, "r");
    if (fh) {
        fclose(fh);     
        return true;
    }
    return false;
}

FILE* fileOpen(const char* filename, const char* mode) {

    if (!filename || !mode) {
        return NULL;
    }

    const WCHAR* wfilename = toWideChar(filename);
    const WCHAR* wmode     = toWideChar(mode);

    // MUST use a wchar_t* to manage correctly international chars.
    // If using char* and UTF-8, fopen() is not working correctly and
    // will fail to open the file, on Windows platform.
    FILE* f = _wfopen(wfilename, wmode);

    delete [] wfilename;
    delete [] wmode;
    return f;
}

bool readFile(const char* path, char **message, size_t *len, bool binary)
{
    bool ret = false;
    FILE *f;
    size_t msglen=0;
    char *msg=0;

    const char* mode = binary ? "rb" : "r";
    f = fileOpen(path, mode);
    if ( !f ) {
        goto finally;
    }
    msglen = fgetsize(f);
    msg = new char[msglen+1];

    *len=fread(msg, sizeof(char), msglen, f);
    if(ferror(f)){
        delete [] msg;
        goto finally;
    }
    fclose(f);

    // Terminate the read msg
    msg[*len] = 0;

    // Set return parameters
    *message= msg ;
    //*len=msglen;
    ret = true;

finally:
    return ret;
}


bool saveFile(const char *filename, const char *buffer, size_t len, bool binary) 
{
    bool ret = false;

    const char* mode = binary ? "wb" : "w";
    FILE *f = fileOpen(filename, mode);
    if(!f) {
        goto finally;
    }

    if (fwrite(buffer, sizeof(char), len, f) != len) {
        fclose(f);
        goto finally;
    }
    fclose(f);
    ret = true;

finally:
    return ret;
}


unsigned long getFileModTime(const char* name) {
	struct stat buffer;
	return stat(name, &buffer) ? 0 : (unsigned long)buffer.st_mtime;
}


StringBuffer unixTimeToString(const unsigned long unixTime, const bool isUTC) {

    StringBuffer ret;
    struct tm sysTime;
    __time64_t tstamp = (__time64_t)unixTime;

    int err = _gmtime64_s(&sysTime, &tstamp);
    if (err) {
        LOG.error("error in _gmtime64_s (code %d)", err);
        return ret;
    }

    int year  = sysTime.tm_year + 1900;  // starting from 1900
    int month = sysTime.tm_mon + 1;      // range [0-11]
    ret.sprintf("%d%02d%02dT%02d%02d%02d", year, month, sysTime.tm_mday, sysTime.tm_hour, sysTime.tm_min, sysTime.tm_sec);

    if (isUTC) {
        ret.append("Z");
    }
    return ret;
}


#if defined(WIN32) || defined(_WIN32_WCE)
/// Returns a file list from a directory, as char**.
char** readDir(const char* name, int *count, bool onlyCount) {

    *count = 0;
    char** fileNames = NULL;
    WIN32_FIND_DATA FileData;
    HANDLE hFind;
    DWORD dwAttrs;
    WCHAR toFind    [512];
    WCHAR szNewPath [512];
    szNewPath[0] = 0;
    bool fFinished = false;

    //
    // Get number of files
    //
    if (!onlyCount) {
        int i=0;
        readDir(name, &i, true);
        if (i>0)
            fileNames = new char*[i];
        else
            return NULL;
    }

    WCHAR* wname = toWideChar(name);
    wsprintf(toFind, TEXT("%s\\*.*"), wname);


    //
    // Get file names from dir
    //
    hFind = FindFirstFile(toFind, &FileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        LOG.error("Invalid handle for retrieve files from %s", name);
        *count = 0;
        fileNames = NULL;
        goto finally;
    }
    else {
        while (!fFinished) {
            wsprintf(szNewPath, TEXT("%s/%s"), wname, FileData.cFileName);
            dwAttrs = GetFileAttributes(szNewPath);

             if (   (dwAttrs & FILE_ATTRIBUTE_DIRECTORY)
                 || (dwAttrs & FILE_ATTRIBUTE_HIDDEN)
                 || (dwAttrs & FILE_ATTRIBUTE_SYSTEM) ) {
             }// nothing
             else {
                 if (!onlyCount) {
                    fileNames[*count] = toMultibyte(FileData.cFileName);
                 }
                (*count) ++;
            }

            if (!FindNextFile(hFind, &FileData)) {
			    if (GetLastError() == ERROR_NO_MORE_FILES){
				    fFinished = true;
			    }
		    }
	    }
        // Close the search handle.
	    FindClose(hFind);
    }

finally:
    if (wname) {
        delete [] wname;
        wname = NULL;
    }
    return fileNames;
}


bool removeFileInDir(const char* d, const char* fname) {
    
    WIN32_FIND_DATA FileData;
    HANDLE hFind;

    wchar_t toFind    [512];
    wchar_t szNewPath [512];    
    bool ret = false;

    DWORD dwAttrs;
    BOOL fFinished = FALSE;
    
    WCHAR* dir      = toWideChar(d);
    
    if (fname) {
        WCHAR* filename = toWideChar(fname);
        wsprintf(toFind, TEXT("%s/%s"), dir, filename);    
        delete [] filename; filename = NULL;
    }
    else {
        wsprintf(toFind, TEXT("%s/*.*"), dir);
    }

    hFind = FindFirstFile(toFind, &FileData);

    if (hFind != INVALID_HANDLE_VALUE) {
        while (!fFinished) {

            wsprintf(szNewPath, TEXT("%s/%s"), dir, FileData.cFileName);
            dwAttrs = GetFileAttributes(szNewPath);
            if (dwAttrs == FILE_ATTRIBUTE_DIRECTORY) { }
                // do anything for subdirectory
            else {
                  DeleteFile(szNewPath);
            }

            if (!FindNextFile(hFind, &FileData)) {
                if (GetLastError() == ERROR_NO_MORE_FILES) {
                    fFinished = TRUE;
                }
                else  {
                    goto finally;
                }
            }
        }

        FindClose(hFind);
    }
    
    ret = true;

finally:
    if (dir) { delete [] dir; }
    return ret;
}

/**
 * Creates a folder, and all needed folders. 
 * @return 0 on success, -1 otherwise.
 */
int createFolder(const char *path) {
    wchar_t *wpath=toWideChar(path);
    wchar_t *tpath=0;
    wchar_t tsep=0;
    int ret = 0;
    BOOL success = 0;

    // Skip C:/
    tpath = wcschr(wpath, ':');
    if(tpath){
        tpath++;
    }
    else {
        tpath = wpath;
    }
    // Create upper folders
    while( (tpath=wcspbrk(tpath+1, TEXT("\\/"))) ) {
        tsep=*tpath;
        *tpath=0;
        success = CreateDirectory(wpath, NULL);
        *tpath=tsep;

        if(!success && GetLastError() != ERROR_ALREADY_EXISTS) {
            LOG.error("createFolder: error creating folder %s", path);
            ret = -1;
            break;
        }
    }
    // Create last folder
    if (ret == 0) {
        success = CreateDirectory(wpath,NULL);
        if(!success && GetLastError() != ERROR_ALREADY_EXISTS) {
            LOG.error("createFolder: error creating folder %s", path);
            ret = -1;
        }
    }
    delete [] wpath;
    return ret;
}

/**
 * return the home folder, or an empty string on failure.
 *
StringBuffer getHomeFolder() {
    wchar_t p[MAX_PATH];
    StringBuffer home(NULL);

    if( !SHGetSpecialFolderPath(NULL, p, CSIDL_PERSONAL, 0)) {
        LOG.error("Can't get home folder.");
    }
    else {
        home.convert(p);
    }
    return home;
}

StringBuffer getConfigFolder(const char *appname) {
    
    StringBuffer ret(".");
    wchar_t appdir[MAX_PATH];
    SHGetSpecialFolderPath(NULL, appdir, CSIDL_APPDATA, 0); 
    ret.convert(appdir);
    return ret;
}
*/

#else
// TBD: dummy implementation!
char** readDir(char* name, int *count, bool onlyCount) {
    return NULL;
}

bool removeFileInDir(const char* dir, const char* filename);
#endif   // #if defined(WIN32) && !defined(_WIN32_WCE)




static int findCodePage(const char *encoding)
{
    if (encoding && strcmp(encoding, "")){
        for(int i=0; encodings[i].name; i++) {
            if(_stricmp(encodings[i].name, encoding) == 0) {
                // Found
                return encodings[i].codepage_id;
            }
        }
        // Not found
        LOG.error("Invalid encoding: %s", encoding);
    }
    // Default encoding
    return CP_UTF8;
}

static size_t getLenEncoding(const WCHAR* s, int codepage)
{
    if (!s)
        return 0;

    int len = wcslen(s);

    if (!len)
        return 0;

    long k = WideCharToMultiByte (codepage, 0, s, len, 0, 0, 0, 0);

    return (k != 0) ? (long)k : -1;
}

size_t getLenEncoding(const WCHAR* s, const char* encoding)
{
    return getLenEncoding( s, findCodePage(encoding) );
}

char* toMultibyte(const WCHAR *wc, const char *encoding)
{
    if (!wc) {
        return NULL;
    }

    char *ret;
    size_t wlen = wcslen(wc);

    if (!wlen) {
        ret = new char[1];
        ret[0] = 0;
        return ret;
    }

    int codepage = findCodePage(encoding);
    size_t blen = getLenEncoding(wc, codepage);

    if(blen <= 0) {
        LOG.error("toMultibyte: invalid encoding");
        return NULL;
    }

    ret = new char[blen+1];

    blen = WideCharToMultiByte(codepage, 0, wc, wlen, ret, blen, 0, 0);
    ret[blen] = 0;

    return ret;
}

WCHAR* toWideChar(const char *mb, const char *encoding) {

    if (mb == NULL) {
        return NULL;
    }

    unsigned long dsize = strlen(mb);
    WCHAR *ret = new WCHAR[dsize+2];
    memset(ret, 0, (dsize + 1)*sizeof(WCHAR));

    if (!dsize)
        return ret;
    int codepage = findCodePage(encoding);
    unsigned long k = 0;

    k = MultiByteToWideChar(codepage, 0, mb, -1, ret, dsize + 1);
    if( !k ) {
        LOG.error("toWideChar: error %d \n\tConverting: %s\n\tWith encoding %s",
            GetLastError(), mb, encoding);
        LOG.error("toWideChar: try to use default codepage.");
        k = MultiByteToWideChar(CP_UTF8, 0, mb, -1, ret, dsize + 1);
        if( !k ){
            LOG.error("toWideChar: error %d converting the string using default codepage.");
            delete [] ret; ret = 0;
        }
    }

    return ret;
}


int round(double val) {
    int v = (int)val;
    return ((val - v) > 0.5) ? v+1 : v;
}

bool setSyncAborted()
{
    HANDLE syncAbortEvent = NULL;
    bool   ret = true;

    syncAbortEvent = CreateEvent( NULL,            // default security attributes
                                  FALSE,           // automatically reset event
                                  FALSE,           // initial state is signaled
                                  TEXT("Global\\AbortSyncEvent") // object name
                                ); 

    if (syncAbortEvent == NULL) {
        DWORD err = GetLastError();
        LOG.error("%s: error creating event object: %d", __FUNCTION__, GetLastError());

        return false;
    }


    if (! SetEvent(syncAbortEvent) ) {
        LOG.error("%s: error signaling event object: %d", __FUNCTION__, GetLastError());

        ret = false; 
    }
 
    return ret;
}

bool checkSyncAborted()
{
    HANDLE syncAbortEvent = NULL;
    DWORD dwWaitResult;
    bool ret = false;

    syncAbortEvent = OpenEvent(EVENT_ALL_ACCESS, 
                               FALSE, 
                               TEXT("Global\\AbortSyncEvent"));

    if (syncAbortEvent == NULL) {
        DWORD err = GetLastError();
        // if event wasn't created don't log any error: 
        if (err != ERROR_FILE_NOT_FOUND) {
            LOG.error("%s: error opening sync abort event: %d", __FUNCTION__, err);
        } 

        return ret;
    }

    dwWaitResult = WaitForSingleObject( syncAbortEvent, 0 );

    switch (dwWaitResult) {
        case WAIT_OBJECT_0: 
            // event object was signaled
            ret = true;
            break; 

        case WAIT_TIMEOUT:
            // event object wasn't signaled
            break;

        default: 
            LOG.error("%s: error waiting for event object (%d)\n", __FUNCTION__, GetLastError());
            break;
    }

    CloseHandle(syncAbortEvent);
  
    return ret;
}

bool resetSyncAborted()
{
    HANDLE syncAbortEvent = NULL;
    bool ret = false;

    syncAbortEvent = OpenEvent(EVENT_ALL_ACCESS, 
                               FALSE, 
                               TEXT("Global\\AbortSyncEvent"));

    if (syncAbortEvent == NULL) {
        DWORD err = GetLastError();
        // if event wasn't created don't log any error: 
        if (err != ERROR_FILE_NOT_FOUND) {
            LOG.error("%s: error opening sync abort event: %d", __FUNCTION__, err);
        } 

        return ret;
    }

    if (! ResetEvent(syncAbortEvent) ) {
        LOG.error("%s: error resetting cancelled sync event handle", __FUNCTION__);
        ret = false;
    }

    CloseHandle(syncAbortEvent);
  
    return ret;
}

#if defined(WIN32) && !defined(_WIN32_WCE)
// ----------------------------------------------------
// REDEFINITION OF NEW / DELETE -> debug for memory leaks
//
// WARNING: this sloooooowwwwssss doooowwwwnnnn things!
// ----------------------------------------------------
#ifdef MALLOC_DEBUG

//
// This is required since in debug mode, new is rewritten
// as new(__FILE__, __LINE__). See utils.h for details
//
#undef new
#include "base/memTracker.h"

MemTracker m = MemTracker(true);

void *operator new(size_t s, char* file, int line) {
	void* p = malloc(s);

	//fprintf(stderr, "new - p:%lx s:%ld, %s:%d\n", p, s, file, line);
	if (m.isMemTracking()) {
 		m.disableMemTracker();
		m.addTrack((DWORD)p, s, file, line);
    	m.enableMemTracker();
	}

	return p;
}

void *operator new(size_t s) {
	return ::operator new(s, "", 0);
}

void *operator new[](size_t s) {
	return ::operator new(s, "", 0);
}

void *operator new[](size_t s, char* file, int line) {
	return ::operator new(s, file, line);
}

void operator delete(void* p) {

	//fprintf(stderr, "delete - p:%lx\n", (long)p);
    if (m.isMemTracking()) {
    	m.disableMemTracker();
		m.removeTrack((DWORD)p);
        m.enableMemTracker();
	}

    if (p) {
    	free(p);
    }
 }

 void operator delete[] (void* p) {
 	::operator delete(p);
 }


 void printMemLeaks() {
 	if (m.isMemTracking())
    	m.dumpUnfreed();
 }

#endif  // #ifdef MALLOC_DEBUG

#endif  // #if defined(WIN32) && !defined(_WIN32_WCE)

END_NAMESPACE