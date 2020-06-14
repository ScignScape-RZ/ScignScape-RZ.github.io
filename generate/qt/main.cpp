

//           Copyright Nathaniel Christen 2020.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include <QFileInfo>
#include <QFile>
#include <QString>
#include <QMap>
#include <QDir>
#include <QTextStream>



QString read_file(QString path)
{
 QString result;
 QFile infile(path);
 if(infile.open(QIODevice::ReadOnly))
 {
  result = infile.readAll();
 }
 return result;
}

QString resolve_web_path(QString path)
{
 //?QFileInfo qfi(web_base_path_);
 //?QDir qd = qfi.absoluteDir();
 //?
 QString result; //? = qd.absoluteFilePath(path);
 return result;
}

QString pics_base_path() {}
QString css_base_path() {}
QString ngml_base_path() {}
QString pdf_base_path() {}

QString resolve_path(QString group, QString path, QString& suffix)
{
#define TEMP_MACRO(key, field) \
 { #key, \
  (QString(*)())(&field) \
 }, \

 static QMap<QString, QString(*)()> static_map
 {
  TEMP_MACRO(pics ,pics_base_path)
  TEMP_MACRO(css ,css_base_path)
  TEMP_MACRO(ngml ,ngml_base_path)
  TEMP_MACRO(pdf ,pdf_base_path)
 };

#undef TEMP_MACRO

 QString result;

 if(static_map.contains(group))
 {
  auto fn = static_map[group];
  QFileInfo qfi; // = (this->*fn)();
  QDir qd = qfi.absoluteDir();
  result = qd.absoluteFilePath(path);
  QFileInfo qfi1(result);
  suffix = qfi1.suffix();
 }
 return result;
}

bool get_content_type(QString key, QString& code)
{
 static QMap<QString, QPair<bool, QString>> static_map {
  {".htm", {false, "text/html"}},
  {".html", {false, "text/html"}},
  {".png", {true, "image/png"}},
  {".gif", {true, "image/gif"}},
  {".jpg", {true, "image/jpg"}},
  {".jpeg", {true, "image/jpeg"}},
  {".wmv", {true, "audio/x-ms-wmv"}},
  {".pdf", {true, "application/pdf"}},

  {"htm", {false, "text/html"}},
  {"html", {false, "text/html"}},
  {"png", {true, "image/png"}},
  {"gif", {true, "image/gif"}},
  {"jpg", {true, "image/jpg"}},
  {"jpeg", {true, "image/jpeg"}},
  {"wmv", {true, "audio/x-ms-wmv"}},
  {"pdf", {true, "application/pdf"}},
 };

 if(static_map.contains(key))
 {
  code = static_map[key].second;
  return static_map[key].first;
 }
 else
 {
  return false;
 }
}


QMap<QString, QString> read_partials_map()
{
 // //  It may be desirable to read these from a file, but by way of illustration ...
 QMap<QString, QString> result;
 return result;
}


QString complete_partials(QString& result,
 QString path, QString default_path)
{
 static QMap<QString, QString> partials_map = read_partials_map();

 QFile infile(path);

 if(infile.open(QIODevice::ReadOnly))
 {
  QTextStream in(&infile);
  while (!in.atEnd())
  {
   QString line = in.readLine();
   if(line.startsWith("@@"))
   {
    QString code = line.mid(2).trimmed();
    QString partial_path = partials_map.value(code);
    if(partial_path.isEmpty())
    {
     QString dp = default_path;

     // //
     if(code.startsWith("top-links"))
      dp += "top-nav";
     else if(code.endsWith("style"))
      dp += "styles";
     else if(code.endsWith("form"))
      dp += "forms";

     if(!default_path.isEmpty())
     {
      partial_path = QString("%1/%2.htm").arg(dp).arg(code);
     }
    }
    if(!partial_path.isEmpty())
    {
     QFile pinfile(partial_path);

     if(pinfile.open(QIODevice::ReadOnly))
     {
      QTextStream pin(&pinfile);
      QString ra = pin.readAll();
      ra.replace("<!--.[", "<!--[");
      ra.replace("<!.[", "<![");
      result += ra;
     }
    }
   }
   else
   {

//?    line.replace("$$CURRENT_DATE_TIME$$", current_date_time);
    line.replace("---", "&mdash;");

    line.replace("#{", "<span class='tterm'>");
    line.replace("}#", "</span>");

    line.replace("#^{", "<span class='tterm-cap'>");
    line.replace("}#", "</span>");

    line.replace("#(", "<span class='acronym'>");
    line.replace(")#", "</span>");

    line.replace("#^(", "<span class='acronym-cap'>");
    line.replace(")#", "</span>");

    line.replace("#[", "<span class='tlink'>");
    line.replace("]#", "</span>");

    line.replace("#^[", "<span class='tlink-cap'>");
    line.replace("]#", "</span>");

    line.replace("*(", "<span class='tquote'>&ldquo;");
    line.replace(")*", "&rdquo;</span>");

    line.replace("*[", "<span class='xquote'>&ldquo;");
    line.replace("]*", "&rdquo;</span>");

    result += line + "\n";
   }
  }
  infile.close();
 }

 return QString();
}


bool handle(QString requrl, QString method,
  QString& response_string)
{

}

int main(int argc, char* argv[])
{
 QString folder;// = cmdl.size() > 2? cmdl[2]: DEFAULT_SDI_FOLDER;
 QString file;// = cmdl.size() > 3? cmdl[3]: DEFAULT_SDI_FOLDER

}



