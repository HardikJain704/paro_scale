const fs = require('fs');
const path = require('path');

function scanDirectory(dirPath) {
  return new Promise((resolve, reject) => {
    let files = 0;
    let subdirectories = 0;

    fs.readdir(dirPath, { withFileTypes: true }, (err, entries) => {
      if (err) {
        return reject(err);
      }

      const processEntry = async (entry) => {
        const entryPath = path.join(dirPath, entry.name);

        if (entry.isDirectory()) {
          subdirectories++;
          const { files: subFiles, subdirectories: subDirs } = await scanDirectory(entryPath);
          files += subFiles;
          subdirectories += subDirs;
        } else if (entry.isFile()) {
          files++;
        }
      };

      const entryPromises = entries.map(processEntry);
      Promise.all(entryPromises)
        .then(() => resolve({ files, subdirectories }))
        .catch(reject);
    });
  });
}

async function countFilesAndDirectories(rootDir) {
  try {
    const { files, subdirectories } = await scanDirectory(rootDir);
    console.log(`Files: ${files}, Subdirectories: ${subdirectories}`);
  } catch (err) {
    console.error('Error:', err);
  }
}

const rootDirectory = '\\Users\\KIIT\\AppData\\Local\\ElevatedDiagnostics'; 
countFilesAndDirectories(rootDirectory);
