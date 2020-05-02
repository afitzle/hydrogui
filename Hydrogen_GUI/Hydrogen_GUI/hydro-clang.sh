cd "$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"
cd TestPrograms/Buggy
clang -c -O0 -Xclang -disable-O0-optnone -g -emit-llvm -S Prog.c -o ProgV1.bc
cd ../Correct
clang -c -O0 -Xclang -disable-O0-optnone -g -emit-llvm -S Prog.c -o ProgV2.bc
cd /home/Hydrogen/MVICFG/BuildNinja
pwd
./Hydrogen.out ../TestPrograms/Buggy/ProgV1.bc ../TestPrograms/Correct/ProgV2.bc :: ../TestPrograms/Buggy/Prog.c :: ../TestPrograms/Correct/Prog.c