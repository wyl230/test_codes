#!/bin/bash
# if $1 has ts, remove ts
npx tsc $1.ts
mv $1.js $1.cjs
node $1.cjs
