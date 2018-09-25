autocmd!bufwritepost $HOME/.vimrc source %

syntax enable
syntax on
set nu
set ruler
set showmode
set cursorline
set cursorcolumn
set hlsearch

filetype indent on 
set expandtab
set tabstop=4
set shiftwidth=4
set softtabstop=4

"Complete '',"",(),[],{}
"Add space to : ,
inoremap ' ''<ESC>i
inoremap " ""<ESC>i
inoremap ( ()<ESC>i
inoremap ) <c-r>=ClosePair(')')<CR>
inoremap [ []<ESC>i
inoremap ] <c-r>=ClosePair(']')<CR>
inoremap { {<CR>}<ESC>O
inoremap , ,<Space>
inoremap : :<Space>
function! ClosePair(char)
    if getline('.')[col('.')-1]==a:char
        return "\<Right>"
    else
        return a:char
    endif
endfunc

"set foldmethod=index
set foldmethod=syntax
set nofoldenable

filetype off
set rtp+=~/.vim/bundle/Vundle.vim

call vundle#begin()
Plugin 'VundleVim/Vundle.vim'
Plugin 'altercation/vim-colors-solarized'
Plugin 'tomasr/molokai'
Plugin 'vim-scripts/phd'
Plugin 'Lokaltog/vim-powerline'
Plugin 'octol/vim-cpp-enhanced-highlight'
Plugin 'nathanaelkane/vim-indent-guides'
Plugin 'derekwyatt/vim-fswitch'
Plugin 'kshenoy/vim-signature'
Plugin 'vim-scripts/BOOKMARKS--Mark-and-Highlight-Full-Lines'
Plugin 'majutsushi/tagbar'
"Plugin 'vim-scripts/indexer.tar.gz'
Plugin 'vim-scripts/DfrankUtil'
Plugin 'vim-scripts/vimprj'
Plugin 'dyng/ctrlsf.vim'
Plugin 'terryma/vim-multiple-cursors'
Plugin 'vim-scripts/DrawIt'
Plugin 'Sirver/Ultisnips'
Plugin 'Valloric/YouCompleteMe'
Plugin 'derekwyatt/vim-protodef'
Plugin 'scrooloose/nerdtree'
Plugin 'fholgado/minibufexpl.vim'
Plugin 'gcmt/wildfire.vim'
Plugin 'sjl/gundo.vim'
Plugin 'Lokaltog/vim-easymotion'
Plugin 'suan/vim-instant-markdown'
Plugin 'lilydjwg/fcitx.vim'
Plugin 'SirVer/ultisnips'
Plugin 'chxuan/change-colorscheme'

Plugin 'Alvarocz/vim-northpole'
Plugin 'Alvarocz/vim-fresh'
Plugin 'kjohnsen/heman'
Plugin 'miconda/lucariox.vim'
Plugin 'wolf-dog/nighted.vim'
Plugin 'skreek/skeletor.vim'
Plugin 'Jimeno0/vim-chito'
call vundle#end()
filetype plugin indent on

set t_Co=256
"colorscheme northpole
"colorscheme heman
colorscheme nighted
"colorscheme lucariox
set guifont=CodeNewRoman\ 12
map <F11> :NextColorScheme<CR>
map <F12> :PreviousColorScheme<CR>  

set smartindent 
set ignorecase

set whichwrap+=<,>,h,l

set backspace=eol,start,indent
set mouse=a
set selection=exclusive
set selectmode=mouse,key

set showmatch
set matchtime=5

map <S-R> :call CompileRunGcc()<CR>
func! CompileRunGcc()
    exec "w"
    if &filetype=='c'
        exec "!g++ % -o %<"
        exec "! ./%<"
    elseif &filetype=='cpp'
        exec "!g++ % -o %<"
        exec "! ./%<"
    endif
endfunc

map <S-D> :call Rungdb()<CR>
func! Rungdb()
    exec "w"
    exec "!g++ % -g -o %<"
    exec "!gdb ./%<"
endfunc
		
"YCM
nnoremap <leader>jc: YcmCompleter GoToDeclaration<CR>
nnoremap <leader>jd: YcmCompleter GoToDeclaration<CR>
let g:ycm_global_ycm_extra_conf='~/.vim/bundle/YouCompleteMe/third_party/ycmd/cpp/ycm/.ycm_extra_conf.py'

"UltiSnips
let g:UltiSnipsExpandTrigger="<leader><tab>"
let g:UltiSnipsJumpForwardTrigger="<leader><tab>"
let g:UltiSnipsJumpBackwardTrigger="<leader><tab>"

