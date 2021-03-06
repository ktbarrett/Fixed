# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.


# -- Project information -----------------------------------------------------

project = 'hdltypes'
copyright = '2020, Kaleb Barrett'
author = 'Kaleb Barrett'

# The full version, including alpha/beta/rc tags
with open('../version') as file:
    release = file.read()

# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    "sphinx.ext.autodoc",
    'sphinx_rtd_theme',
    "breathe"
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'sphinx_rtd_theme'


# -- Run doxygen -------------------------------------------------------------

# This is less than ideal
# ReadTheDocs has no official support for doxygen as a part of its
# documentation generation flow. To circumvent this we call doxygen from the
# configuration file so it runs doxygen when sphinx is first invoked
import subprocess
subprocess.run(['doxygen', 'Doxyfile'])


# -- Breathe extension -------------------------------------------------------

breathe_projects = {'hello': "_doxygen_build/xml"}
breathe_default_project = "hello"
