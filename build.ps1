# build.ps1
Param(
  $type
)

If(-Not $type -eq ''){
  Write-Host "Configuring and building in Debug" 
  cmake -DCMAKE_BUILD_TYPE=Debug -B build
} ElseIf($type -eq "Release"){
  Write-Host "Configuring and building in Release" 
  cmake -DCMAKE_BUILD_TYPE=Release -B build
}
  Else{
  Write-Host "Default Configuration and Building"
  cmake -B build
}
cmake --build build

