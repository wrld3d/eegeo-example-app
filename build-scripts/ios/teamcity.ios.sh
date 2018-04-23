#!/bin/sh

xcodeTargetName=$1
productName=$2
productVersion=$3
teamcityBuildUrl=$4
githubCommitUrl=$5
pathToProjectDir=${6}
hockeyAppIdentifier=${7:-d7b222a21f80e5f429f395652ff06924}
environment=${8:staging}
provisioningProfile=$9

# This script executes all the steps to produce an iOS app.

if [[ ( $environment != 'staging' ) && ( $environment != 'production' ) && ( $environment != 'release' ) ]]; then
  echo "invalid environment '$environment'. Must be one of [staging|production|release]"
  exit 1
fi


rm -rf $pathToProjectDir"/build"

archivePath="./Swallow$environment.xcarchive"
ipaName="Swallow$environment"

sh "build-scripts/ios/compile_xcode.step.sh" $xcodeTargetName $productName $productVersion $pathToProjectDir $archivePath

if [ $? -ne 0 ] ; then
  git checkout $file_to_poke
  exit 1
fi

git checkout $file_to_poke

sh "build-scripts/ios/create_ipa_file.step.sh" $productName.app $pathToProjectDir $archivePath $ipaName $provisioningProfile
if [ $? -ne 0 ] ; then
  exit 1
fi

sh "build-scripts/ios/commit_to_hockeyapp.step.sh" $teamcityBuildUrl $githubCommitUrl $pathToProjectDir $xcodeTargetName $hockeyAppIdentifier
if [ $? -ne 0 ] ; then
exit 1
fi

# TODO: fail build if the final app size is too big.

echo
echo "BUILD SUCCEEDED"
echo

exit 0
