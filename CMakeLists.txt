cmake_minimum_required(VERSION 3.10)

# 프로젝트 이름과 버전을 설정하세요
project(MyRaylibProject VERSION 1.0)

# 필요한 C++ 표준을 설정하세요 (필요에 따라 변경)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# raylib 헤더 파일 경로 찾기
find_path(RL_INCLUDE_DIR raylib.h PATHS /opt/homebrew/opt/raylib/include)
include_directories(${RL_INCLUDE_DIR})

# include 디렉토리 추가
include_directories(include)

# src 디렉토리의 소스 파일들을 변수에 저장
set(SRC_FILES src/circular_queue.c src/player.c src/slime.c src/weapon.c)


# raylib 라이브러리 경로 찾기
find_library(RL_LIBRARY raylib PATHS /opt/homebrew/opt/raylib/lib)

# 경로 출력 (디버깅 용도)
# message("Raylib include directory: ${RL_INCLUDE_DIR}")
# message("Raylib library: ${RL_LIBRARY}")

# test 디렉토리의 메인 파일을 변수에 저장
set(TEST_FILES test/main.c)

# 실행 파일 생성
add_executable(MyRaylibProject ${SRC_FILES} ./test/main.c)

# raylib 라이브러리와 링크
target_link_libraries(MyRaylibProject ${RL_LIBRARY})
