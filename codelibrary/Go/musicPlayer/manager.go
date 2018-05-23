/*我们先定义音乐的结构体
type Music struct {
	Id string 	//唯一的ID
	Name string	//音乐名
	Artist string	//艺术家名
	Source string	//音乐位置
	Type string //音乐文件类型（MP3和WAV等）
}*/

/*我们先实现这个音乐库管理类型，其中我们使用了一个数组切片作为基础
存储结构，其他的操作都是对这个数组切片的包装*/

package library
import "errors"

type MusicManager struct {
	musics []MusicEntry
}

func NewMusicManager() *MusicManager {
	return &MusicManager{make([]MusicEntry,0)}
}

func (m *MusicManager) len() int {
	return len(m.musics)
}