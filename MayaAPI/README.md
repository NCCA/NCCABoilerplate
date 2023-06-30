# Simple Maya API Example

This example uses the maya devkit cmake templates to build a simple plugin that creates a simple command. For more examples see the plugins folder in the maya devkit download.

First we need to download the devkit from [here](https://www.autodesk.com/developer-network/platform-technologies/maya) In the labs it is installed in  /public/devel/23-24/maya2023_dev for maya 2023 and /public/devel/23-24/maya2024_dev for maya 2024. 

To use this you will need to set the following variables when building 

```bash
-DDEVKIT_LOCATION=/path/to/devkit
```

Typically I add the location in the .bashrc file so that it is always set. 


