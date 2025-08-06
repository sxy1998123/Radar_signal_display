import axios from 'axios'
const backendUrl = window.electronAPI && window.electronAPI.backendUrl ? window.electronAPI.backendUrl : ''
export default {
    generateSignal: (data) => {
        return axios.post(`${backendUrl}/api/signal/generate`, data)
    },
    handleSignal: (data) => {
        return axios.post(`${backendUrl}/api/signal/handle`, data)
    },
    collectSignal: (data) => {
        return axios.post(`${backendUrl}/api/signal/collect_start`, data)
    },
    endCollectSignal: () => {
        return axios.get(`${backendUrl}/api/signal/collect_end`)
    }
}