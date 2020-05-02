cd "$(dirname "$(readlink -f "${BASH_SOURCE[0]}")")"
./Hydrogen.out ../TestPrograms/Buggy/ProgV1.bc ../TestPrograms/Correct/ProgV2.bc :: ../TestPrograms/Buggy/Prog.c :: ../TestPrograms/Correct/Prog.c