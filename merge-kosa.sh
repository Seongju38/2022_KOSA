#!/bin/bash

# 저장소 리스트
REPOS=(
  "DailyHW"
  "HWCalc"
  "HWMemberMgr"
  "HWModalDemo"
  "MFCODBC_EXAM"
  "HWDraw"
  "HWHospital"
  "AspdotnetReact"
)

# 현재 브랜치 이름 감지
CURRENT_BRANCH=$(git symbolic-ref --short HEAD)

echo "📍 현재 브랜치: $CURRENT_BRANCH"

for REPO in "${REPOS[@]}"
do
  echo "🔄 Processing $REPO ..."

  # 원격 추가 & 가져오기
  git remote add $REPO https://github.com/Seongju38/$REPO.git
  git fetch $REPO

  # 브랜치 이름 감지
  DEFAULT_BRANCH=$(git remote show $REPO | grep 'HEAD branch' | awk '{print $NF}')
  echo "📍 $REPO 기본 브랜치: $DEFAULT_BRANCH"

  # 임시 브랜치로 체크아웃
  git checkout -b import-$REPO $REPO/$DEFAULT_BRANCH

  # 폴더로 이동
  mkdir -p $REPO
  git ls-tree -z --name-only HEAD | xargs -0 -I {} git mv {} $REPO/ 2>/dev/null

  # 커밋
  #git commit -m "📦 Move $REPO into subfolder with history"
  git commit -m "moved $REPO into subfolder"

  # 메인 브랜치로 돌아가서 병합
  git checkout $CURRENT_BRANCH
  #git merge import-$REPO --allow-unrelated-histories -m "🔀 Merge $REPO into $CURRENT_BRANCH"
  git merge import-$REPO --allow-unrelated-histories

  # 정리
  git remote remove $REPO
  git branch -D import-$REPO

  echo "✅ $REPO merged successfully!"
done

# 최종 푸시
echo "🚀 Pushing changes to GitHub branch: $CURRENT_BRANCH"
git push origin $CURRENT_BRANCH

echo "🎉 Done! All repositories merged into 2022_KOSA ($CURRENT_BRANCH)."