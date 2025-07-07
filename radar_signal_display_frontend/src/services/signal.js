import axios from 'axios'
export default {
    generateSignal: (data) => {
        return axios.post('/api/signal/generate', data)
    },
    handleSignal: (data) => {
        return axios.post('/api/signal/handle', data)
    }
}