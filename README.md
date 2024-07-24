# 빌드방법
- cmake로 작성하였고, Cmake는 통한 프로젝트 결과는 `Xcode 15`와 `Visual Studio 2022`로만 테스트 하였습니다.
- cmake 최소 버전은 3.10으로 설정하였지만, 저는 3.29.2버전에서 실행하였습니다.
- Cmake로 빌드하려면, 루트 디렉토리에서 다음 명령어를 실행하면 됩니다.

## Xcode(MacOS, LLVM compiler)

- 아래의 cmake 명령어를 통해 Xcode 프로젝트 생성
```bash
cmake -G "Xcode" -B {{build directory}}
```
- 아후 {{build directory}} 으로 이동해서 xcode 프로젝트 파일인 `ExampleTest.xcodeproj`을 실행하고 빌드, 실행하면 됩니다.


## Visual Studio 2022

- 아래의 cmake 명령어를 통해 Xcode 프로젝트 생성
```bash
cmake -G "Visual Studio 17 2022" -B {{build directory}}
```

- 아후 {{build directory}} 으로 이동해서 xcode 프로젝트 파일인 `ExampleTest.sln`을 실행하고 빌드, 실행하면 됩니다.
