import axios from 'axios'
const backendUrl = window.electronAPI && window.electronAPI.backendUrl ? window.electronAPI.backendUrl : ''
export default {
    generateSignal: (data) => {
        return axios.post(`${backendUrl}/api/signal/generate`, data)
    },
    handleSignal: (data) => {
        return axios.post(`${backendUrl}/api/signal/handle`, data)
    }
}