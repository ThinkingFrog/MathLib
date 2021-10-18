cd VectorImpl
call build.bat

cd ..\SetImpl
mkdir lib
copy ..\VectorImpl\build\libVectorImpl.dll /B lib\libVectorImpl.dll /Y
copy ..\VectorImpl\build\libVectorImpl.dll.a /B lib\libVectorImpl.dll.a /Y
call build.bat

cd ..\CompactImpl
mkdir lib
copy ..\VectorImpl\build\libVectorImpl.dll /B lib\libVectorImpl.dll /Y
copy ..\VectorImpl\build\libVectorImpl.dll.a /B lib\libVectorImpl.dll.a /Y
call build.bat

cd ..\Interface-test
mkdir lib
copy ..\VectorImpl\build\libVectorImpl.dll /B lib\libVectorImpl.dll /Y
copy ..\VectorImpl\build\libVectorImpl.dll.a /B lib\libVectorImpl.dll.a /Y
copy ..\SetImpl\build\libSetImpl.dll /B lib\libSetImpl.dll /Y
copy ..\SetImpl\build\libSetImpl.dll.a /B lib\libSetImpl.dll.a /Y
copy ..\CompactImpl\build\libCompactImpl.dll /B lib\libCompactImpl.dll /Y
copy ..\CompactImpl\build\libCompactImpl.dll.a /B lib\libCompactImpl.dll.a /Y
call build.bat
copy ..\VectorImpl\build\libVectorImpl.dll /B build\libVectorImpl.dll /Y
copy ..\VectorImpl\build\libVectorImpl.dll.a /B build\libVectorImpl.dll.a /Y
copy ..\SetImpl\build\libSetImpl.dll /B build\libSetImpl.dll /Y
copy ..\SetImpl\build\libSetImpl.dll.a /B build\libSetImpl.dll.a /Y
copy ..\CompactImpl\build\libCompactImpl.dll /B build\libCompactImpl.dll /Y
copy ..\CompactImpl\build\libCompactImpl.dll.a /B build\libCompactImpl.dll.a /Y
build\InterfaceTest.exe
cd ..
