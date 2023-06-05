$zipFilePath = ".\pvz.zip"
if (Test-Path $zipFilePath) {
    Remove-Item $zipFilePath -Force
}

Compress-Archive -Path .\CMakeLists.txt, .\src\ -DestinationPath $zipFilePath
