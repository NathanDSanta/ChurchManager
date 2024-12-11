# build.ps1
Param(
  $Type
)

If($Type -eq ''){
  Write-Host "Configuring and building in Debug" 
  cmake -DCMAKE_BUILD_TYPE=Debug -B build
} ElseIf($Type -eq "Release"){
  Write-Host "Configuring and building in Release" 
  cmake -DCMAKE_BUILD_TYPE=Release -B build
}
  Else{
  Write-Host "Default Configuration and Building"
  cmake -B build
}
cmake --build build

