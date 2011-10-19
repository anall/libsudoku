# Copyright 2010-2011 Andrea Nall
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

def runUnitTest(env,target,source):
    import subprocess
    app = str(source[0].abspath)
    if not subprocess.call(app):
       open(str(target[0]),'w').write("PASSED\n")

try:
    Import('opts')
except:
    opts = {}

try:
    Import('env')
except:
    env = Environment()

rdata = {}

env.Append(CPPPATH=['bld'])
Export('env')
Export('rdata')

SConscript("src/SConscript", variant_dir="bld/sudoku")
SConscript("test/SConscript", variant_dir="bld/test")

Default(rdata['lib'])
Alias('build-test',rdata['test'])

test_alias = Command('.passed', "bld/run_tests", runUnitTest)
Depends(test_alias,rdata['test'])
AlwaysBuild(test_alias)
Alias('test',test_alias)