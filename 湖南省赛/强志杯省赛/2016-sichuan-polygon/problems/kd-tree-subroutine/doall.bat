rem   *** validation ***
call scripts\run-validator-tests.bat
call scripts\run-checker-tests.bat

rem    *** tests ***
md tests
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 1" "tests\03" 3
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 2" "tests\04" 4
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 3" "tests\05" 5
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 4" "tests\06" 6
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 5" "tests\07" 7
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 6" "tests\08" 8
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 7" "tests\09" 9
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 8" "tests\10" 10
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 9" "tests\11" 11
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 10" "tests\12" 12
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 11" "tests\13" 13
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 12" "tests\14" 14
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 13" "tests\15" 15
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 14" "tests\16" 16
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 15" "tests\17" 17
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 16" "tests\18" 18
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 17" "tests\19" 19
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 18" "tests\20" 20
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 19" "tests\21" 21
call scripts\gen-input-via-stdout.bat "files\random.exe 3 1 20" "tests\22" 22
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 1" "tests\23" 23
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 2" "tests\24" 24
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 3" "tests\25" 25
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 4" "tests\26" 26
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 5" "tests\27" 27
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 6" "tests\28" 28
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 7" "tests\29" 29
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 8" "tests\30" 30
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 9" "tests\31" 31
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 10" "tests\32" 32
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 11" "tests\33" 33
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 12" "tests\34" 34
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 13" "tests\35" 35
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 14" "tests\36" 36
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 15" "tests\37" 37
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 16" "tests\38" 38
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 17" "tests\39" 39
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 18" "tests\40" 40
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 19" "tests\41" 41
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10 20" "tests\42" 42
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 1" "tests\43" 43
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 2" "tests\44" 44
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 3" "tests\45" 45
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 4" "tests\46" 46
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 5" "tests\47" 47
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 6" "tests\48" 48
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 7" "tests\49" 49
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 8" "tests\50" 50
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 9" "tests\51" 51
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 10" "tests\52" 52
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 11" "tests\53" 53
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 12" "tests\54" 54
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 13" "tests\55" 55
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 14" "tests\56" 56
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 15" "tests\57" 57
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 16" "tests\58" 58
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 17" "tests\59" 59
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 18" "tests\60" 60
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 19" "tests\61" 61
call scripts\gen-input-via-stdout.bat "files\random.exe 3 10000 20" "tests\62" 62
call scripts\gen-answer.bat tests\01 tests\01.a "tests" ""
call scripts\gen-answer.bat tests\02 tests\02.a "tests" ""
call scripts\gen-answer.bat tests\03 tests\03.a "tests" ""
call scripts\gen-answer.bat tests\04 tests\04.a "tests" ""
call scripts\gen-answer.bat tests\05 tests\05.a "tests" ""
call scripts\gen-answer.bat tests\06 tests\06.a "tests" ""
call scripts\gen-answer.bat tests\07 tests\07.a "tests" ""
call scripts\gen-answer.bat tests\08 tests\08.a "tests" ""
call scripts\gen-answer.bat tests\09 tests\09.a "tests" ""
call scripts\gen-answer.bat tests\10 tests\10.a "tests" ""
call scripts\gen-answer.bat tests\11 tests\11.a "tests" ""
call scripts\gen-answer.bat tests\12 tests\12.a "tests" ""
call scripts\gen-answer.bat tests\13 tests\13.a "tests" ""
call scripts\gen-answer.bat tests\14 tests\14.a "tests" ""
call scripts\gen-answer.bat tests\15 tests\15.a "tests" ""
call scripts\gen-answer.bat tests\16 tests\16.a "tests" ""
call scripts\gen-answer.bat tests\17 tests\17.a "tests" ""
call scripts\gen-answer.bat tests\18 tests\18.a "tests" ""
call scripts\gen-answer.bat tests\19 tests\19.a "tests" ""
call scripts\gen-answer.bat tests\20 tests\20.a "tests" ""
call scripts\gen-answer.bat tests\21 tests\21.a "tests" ""
call scripts\gen-answer.bat tests\22 tests\22.a "tests" ""
call scripts\gen-answer.bat tests\23 tests\23.a "tests" ""
call scripts\gen-answer.bat tests\24 tests\24.a "tests" ""
call scripts\gen-answer.bat tests\25 tests\25.a "tests" ""
call scripts\gen-answer.bat tests\26 tests\26.a "tests" ""
call scripts\gen-answer.bat tests\27 tests\27.a "tests" ""
call scripts\gen-answer.bat tests\28 tests\28.a "tests" ""
call scripts\gen-answer.bat tests\29 tests\29.a "tests" ""
call scripts\gen-answer.bat tests\30 tests\30.a "tests" ""
call scripts\gen-answer.bat tests\31 tests\31.a "tests" ""
call scripts\gen-answer.bat tests\32 tests\32.a "tests" ""
call scripts\gen-answer.bat tests\33 tests\33.a "tests" ""
call scripts\gen-answer.bat tests\34 tests\34.a "tests" ""
call scripts\gen-answer.bat tests\35 tests\35.a "tests" ""
call scripts\gen-answer.bat tests\36 tests\36.a "tests" ""
call scripts\gen-answer.bat tests\37 tests\37.a "tests" ""
call scripts\gen-answer.bat tests\38 tests\38.a "tests" ""
call scripts\gen-answer.bat tests\39 tests\39.a "tests" ""
call scripts\gen-answer.bat tests\40 tests\40.a "tests" ""
call scripts\gen-answer.bat tests\41 tests\41.a "tests" ""
call scripts\gen-answer.bat tests\42 tests\42.a "tests" ""
call scripts\gen-answer.bat tests\43 tests\43.a "tests" ""
call scripts\gen-answer.bat tests\44 tests\44.a "tests" ""
call scripts\gen-answer.bat tests\45 tests\45.a "tests" ""
call scripts\gen-answer.bat tests\46 tests\46.a "tests" ""
call scripts\gen-answer.bat tests\47 tests\47.a "tests" ""
call scripts\gen-answer.bat tests\48 tests\48.a "tests" ""
call scripts\gen-answer.bat tests\49 tests\49.a "tests" ""
call scripts\gen-answer.bat tests\50 tests\50.a "tests" ""
call scripts\gen-answer.bat tests\51 tests\51.a "tests" ""
call scripts\gen-answer.bat tests\52 tests\52.a "tests" ""
call scripts\gen-answer.bat tests\53 tests\53.a "tests" ""
call scripts\gen-answer.bat tests\54 tests\54.a "tests" ""
call scripts\gen-answer.bat tests\55 tests\55.a "tests" ""
call scripts\gen-answer.bat tests\56 tests\56.a "tests" ""
call scripts\gen-answer.bat tests\57 tests\57.a "tests" ""
call scripts\gen-answer.bat tests\58 tests\58.a "tests" ""
call scripts\gen-answer.bat tests\59 tests\59.a "tests" ""
call scripts\gen-answer.bat tests\60 tests\60.a "tests" ""
call scripts\gen-answer.bat tests\61 tests\61.a "tests" ""
call scripts\gen-answer.bat tests\62 tests\62.a "tests" ""

