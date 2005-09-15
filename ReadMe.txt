Ключики angel.ini

/////////////////////////////
[General]
ProcessPriority=0

LoadTopdataForPlugins=0
LoadMarkTopicForPlugins=0
LoadCellsForPlugins=0

EnableConsole=1

[Rules]
fix_unarmored_bug=1
/////////////////////////////
при запуске проверяется список GameFile в Morrowind.ini
и делается попытка загрузить файлы *.top *.cel *.mrk
для плагинов эти файлы загружаются только если установлены переменные

[General]
LoadTopdataForPlugins=0
LoadMarkTopicForPlugins=0
LoadCellsForPlugins=0

в angel.ini
