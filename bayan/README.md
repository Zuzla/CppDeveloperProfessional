# Утилита для обнаружения файлов-дубликатов, разаработана с применением библиотеки Boost.

## Опции программы:
-h [ --help ] Help screen
-d [ --directory ] directories to scan (there may be several)
-ed [ --ex_directory ] directories to exclude from scanning (there may be several)
-l [ --level ] scan level (one for all directories, 0 - only the specified directory without attachments)
-fs [ --file_size ] minimum file size, by default, all files larger than 1 byte are checked
-m [ --mask ] masks of file names allowed for comparison
                    * denotes any character or string of characters,
                    ? denotes any one character.
-sb [ --size_block ] Hash algo md5/sha1 (default md5) the block size that reads files (default 1 byte)
-H [ --hash ] one of the available Hashing algorithms md5/sha1 (default md5)

Пример
bayan --directory /home/ilya/Documents/Otus/ --ex_directory /home/ilya/Documents/Otus/bayan --level 1 --file_size 1 --mask "*.cpp" --size_block 256 --hash md5