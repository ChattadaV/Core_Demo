if not exist input ( md input )
if not exist output ( md output )

core_demo.exe /file_read_fgetc Sample_wiki.txt > output\file_read_fgetc.out
core_demo.exe /file_read_fscanf Sample_wiki.txt > output\file_read_fscanf.out
core_demo.exe /string_find banana na > output\string_find.out
core_demo.exe /string_compare Hamster hamster case_sensitive > output\string_compare.out
core_demo.exe /string_compare Hamster hamster case_insensitive >> output\string_compare.out
core_demo.exe /string_split Myers,Gregory,C,gmyers , > output\string_split.out